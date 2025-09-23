// Interface for a stack to store integers
// Author: Edward Alayu
// Date: September 2025

class Stack {
public:
	// Constructors and destructor
	Stack(); // Default constructor
	Stack(int sz);

	void push (int value);

	int pop();

	int peek();

	// return number of elements in stack
	int size();

	// returns true iff stack is empty
	bool empty();

	// prints contents of stack
	void print();

private:
	// Array implementation
	int* arr;
	int top;
	int capacity;

};

