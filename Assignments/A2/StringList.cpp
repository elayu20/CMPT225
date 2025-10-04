// Edward Alayu
// CMPT225
// October 3, 2025
// StringList.cpp

#include "StringList.h"
#include <stdexcept>
#include <iostream>
using std::out_of_range;
using std::cout;
using std::endl;

// Default constructor - makes an empty list of capacity 10
StringList::StringList()
{
	capacity = 10;
	n = 0;
	arr = new string[capacity];
}

// Copy constructor
StringList::StringList(const StringList& other)
{
	copyList(other);
}

// ***UNDOABLE
// Overloaded assignment operator
StringList& StringList::operator=(const StringList& other)
{
	if(&other != this)
	{
		if (undoing == false) {
			// Push its inverse operation to undo stack
			string command = "OAOSET";
			// Goes through each string in list and adds to command
			for (int i = 0; i < size(); i++) {
				command += " " + arr[i];
			}
			undoStack.push(command);
		}

		delete[] arr;
		arr = nullptr; // Avoids dangling pointers

		copyList(other);
	}
	return *this;
}

// Destructor
StringList::~StringList()
{
	delete[] arr;
	arr = nullptr;
}

// ACCESSORS
// Returns the number of elements in the list
int StringList::size() const
{
	return n;
}

// Returns true if the list is empty, false otherwise
bool StringList::empty() const
{
	return n == 0;
}

// Returns the string at the given index
string StringList::get(int i) const
{
	checkBounds(i, "get");
	return arr[i];
}

// Returns the index of the first occurrence of the given string
int StringList::index(string s) const
{
	int i = 0;
	while (i < n && s != arr[i]) {
		i++;
	}
	if (i == n) {
		return -1;
	}
	else {
		return i;
	}
}

// Returns true iff the given string is in the list
bool StringList::contains(string str) const
{
	return !(index(str) == -1);
}

// Returns true if the two lists are equal, false otherwise.
// Does *not* consider any undo information when comparing two Stringlists. All
// that matters is that they have the same strings in the same order.
bool StringList::operator==(const StringList& sl) const
{
	if (size() != sl.size())
	{
		return false;
	}
	for (int i = 0; i < size(); i++)
	{
		if (get(i) != sl.get(i))
		{
			return false;
		}
	}
	return true;
}

// Returns true if the two lists are not equal, false otherwise
bool StringList::operator!=(const StringList& sl) const
{
	return !(*this == sl);
}

// Returns a string representation of the list.
string StringList::toString() const
{
	string result = "{";
	for (int i = 0; i < size(); i++)
	{
		if (i > 0) {
			result += ", ";
		}
		result += "\"" + get(i) + "\"";
	}
	return result + "}";
}


// MUTATORS

// ***UNDOABLE
// Sets the value at the given index
void StringList::set(int i, string str)
{
	checkBounds(i, "set");	
	if (undoing == false) {
		// Pushes undo command
		string command = "SET ";
		command += std::to_string(i) + " " + arr[i];
		undoStack.push(command);
	}

	arr[i] = str;
}

// ***UNDOABLE
// Inserts the given string *before* the given index
void StringList::insertBefore(int pos, string str)
{
	// Doesn't use checkBounds because it's okay to insert at the end
	if (pos < 0 || pos > size()) {
		throw out_of_range("StringList::insertBefore index out of bounds");
	}
	checkCapacity();
	for (int i = n; i > pos; i--) {
		arr[i] = arr[i-1];
	}
	arr[pos] = str;
	n++;

	// Pushes undo command
	if (undoing == false) {
		string command = "REMOVE ";
		command += std::to_string(pos);
		undoStack.push(command);
	}
}

// ***UNDOABLE
// Inserts the given string at the front of the list
void StringList::insertFront(string str)
{
	checkCapacity();
	insertBefore(0, str); // insertBefore already takes care of undoing command
}

// ***UNDOABLE
// Inserts the given string at the back of the list
void StringList::insertBack(string str)
{
	checkCapacity();
	insertBefore(n, str); // insertBefore already takes care of undoing command
}

// ***UNDOABLE
// Removes the element at the given index and moves elements after it down
void StringList::remove(int pos)
{
	checkBounds(pos, "remove");

	// Pushes undo command
	if (undoing == false) {
		string command = "INSERT ";
		command += std::to_string(pos) + " " + arr[pos];
		undoStack.push(command);
	}

	for (int i = pos; i < n - 1; i++) {
		arr[i] = arr[i + 1];
	}
	n--;
}

// ***UNDOABLE
// Empties the list
void StringList::removeAll()
{
	// Pushes undo command
	if (undoing == false) {
		if (!empty()) {
			string command = "SETALL";
			for (unsigned int i = 0; i < size(); i++) {
				command += " " + arr[i];
			}
			undoStack.push(command);
		}
	}
	
	for (int i = 0; i < n; i++) {
		arr[i] = "";
	}
	n = 0;
}

// Undoes the last operation that modified the list
void StringList::undo()
{
	// TO DO
	// Throw an out of range error if stack is empty
	if (undoStack.empty()) {
		throw out_of_range("Nothing to undo");
	}
	undoing = true;

	// Remove command at top of stack and return to previousCommand
	string previousCommand = undoStack.pop();
	
	// Parse string into a method call
	
	// Undo overloaded assignment operator
	// Assume command is "OAOSET {string1} {string2} {string...}"
	// Create a temporary list and parse strings in command into tempList
	// Copy tempList to current list using copyList()
	if(previousCommand.substr(0, 6) == "OAOSET") {
		StringList tempList;
		size_t position = 7; // Start just after "OAOSET "
		
		// Iterate through string list in inverse operation command of assignment operator
		while (position < previousCommand.length()) {
			size_t nextSpace = previousCommand.find(" ", position); // Finds the next space in between strings
			string value;

			// If can't find any more spaces, reached end of string
			// Gets the last string in string list and sets position to end of string to stop loop
			if (nextSpace == string::npos) {
				value = previousCommand.substr(position);
				position = previousCommand.length();
			}
			else {
				value = previousCommand.substr(position, nextSpace - position); // Gets the next string
				position = nextSpace + 1; // Move position past space for next string
			}
			tempList.insertBack(value);
		}

		// Restore the original list state
		copyList(tempList);
	}
	// Undo removeAll() method
	// Assume command is "SETALL {string1} {string2} {string...}"
	else if(previousCommand.substr(0, 6) == "SETALL") {
		StringList tempList;
		size_t position = 7; // Start just after "SETALL "

		// Iterate through string list in inverse operation command of removeAll
		while (position < previousCommand.length()) {
			size_t nextSpace = previousCommand.find(" ", position);
			string value;

			if (nextSpace == string::npos) {
				value = previousCommand.substr(position);
				position = previousCommand.length();
			}
			else {
				value = previousCommand.substr(position, nextSpace - position);
				position = nextSpace  + 1;
			}
			tempList.insertBack(value);
		}
		// Restore the original list state
		copyList(tempList);
	}
	// Undo set() method
	// Assume command is "SET {index} {value}"
	else if (previousCommand.substr(0, 3) == "SET") {
		// pos1 and pos2 are used to find the index position string, then converts it to an integer
		size_t pos1 = previousCommand.find(" "); // Sets pos1 as the index number of the first space after "SET"
		size_t pos2 = previousCommand.find(" ", pos1+1); // Sets pos2 as the index number of the second space after {index}
		int index = std::stoi(previousCommand.substr(pos1+1, pos2-pos1-1)); // Gets index and converts to string, works for index of n many digits
		string value = previousCommand.substr(pos2 + 1); // Gets the string in {value}
		set(index, value); // Calls set method and undos
	}
	// Undo all insert methods
	// Assume command is "REMOVE {position}"
	else if (previousCommand.substr(0, 6) == "REMOVE") {
		int index = std::stoi(previousCommand.substr(7)); // Argument 7 for substr refers to {position}, which works for n amount of digits
		remove(index); 	
	}
	// Undo remove() method
	// Assume command is "INSERT {position} {value}"
	else if (previousCommand.substr(0, 6) == "INSERT") {
		size_t pos1 = previousCommand.find(" "); // First space after INSERT
		size_t pos2 = previousCommand.find(" ", pos1+1); // Second space after {position}
		int index = std::stoi(previousCommand.substr(pos1+1, pos2-pos1-1));
		string value = previousCommand.substr(pos2+1);
		insertBefore(index, value);
	}
	
	undoing = false;
}

// Prints the list
void StringList::print() const
{
	cout << "{";
	for (int i = 0; i < n; i++) {
		cout << " " << arr[i];
	}
	cout << " }" << endl;
}

// Helper function for checking index bounds.
void StringList::checkBounds(int i, string s) const
{
	if (i < 0 || i >= size()) {
		throw out_of_range("StringList::" + s + " index out of bounds");
	}
}

// POST: Doubles the capacity of the list if n == capacity
void StringList::checkCapacity()
{
	if (n == capacity) {
		capacity *= 2;
		string* temp = new string[capacity];
		
		for (int i = 0; i < n; i++) {
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}
}

// Helper function to copy the contents of another list
void StringList::copyList(const StringList& lst)
{
	if (arr != nullptr) {
		delete[] arr;
		arr = nullptr;
	}

	capacity = lst.capacity;
	n = lst.n;
	arr = new string[capacity];

	for (int i = 0; i < n; i++) {
		arr[i] = lst.arr[i];
	}
}

// Default constructor for stack with a capacity of 4
StringList::UndoStack::UndoStack() {
	capacity = 4;
	top = -1;
	stackArr = new string[capacity];
}

// Stack Destructor
StringList::UndoStack::~UndoStack() {
	delete[] stackArr;
}

// Add a undo command to the top of stack
void StringList::UndoStack::push(string command) {
	// Check capacity first
	checkCapacity();

	stackArr[++top] = command;
}

// Remove and return command at the top of the stack
string StringList::UndoStack::pop() {
	if (empty()) {
		throw out_of_range("Stack is empty.");
	}

	return stackArr[top--];
}

bool StringList::UndoStack::empty() const {
	return top == -1;
}

// Doubles capacity of undo stack if top = capacity
void StringList::UndoStack::checkCapacity() {
	if (top + 1 == capacity) {
		capacity *= 2;
		string* temp = new string[capacity];

		for (int i = 0; i <= top; i++) {
			temp[i] = stackArr[i];
		}
		delete[] stackArr;
		stackArr = temp;
	}
}

// FOR DEBUGGING
// PLEASE DELETE BEFORE SUBMITTING
void StringList::UndoStack::debugPrint() const {
	if (empty()) {
		throw out_of_range("Stack is empty.");
	}
	cout << endl;
	for (int i = top; i >= 0; i--) {
		cout << stackArr[i] << endl;
	}
	cout << endl;
}
void StringList::debugUndoStack() const {
	undoStack.debugPrint();
}
