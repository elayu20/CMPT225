#include "Stack.h"
#include <stdexcept>
#include <iostream>
using std::cout;
using std::endl;
using std::out_of_range;
// Default constructor to create an empty stack of size 10
Stack::Stack()
{
// Note - not giving Stack a max size
top = nullptr;
}
// Constructor to creat an empty stack of size n
Stack::Stack(int n)
{
// Note - not giving Stack a max size
// Arguably could add a capacity attribute and throw exception when "full"
top = nullptr;
}
// Copy constructor
Stack::Stack(const Stack& st)
{
copyHelper(st);
}
// Overloaded assignment operator
Stack& Stack::operator=(const Stack& st)
{
if (&st != this) {
deleteStack();
copyHelper(st);
}
return *this;
}
// Destructor
Stack::~Stack()
{
deleteStack();
}
// Makes calling object new stack containing values in st
void Stack::copyHelper(const Stack& st)
{
if (st.top == nullptr) {
top = nullptr;
}
else {
// Handle top node
top = new Node(st.top->data);
Node* original = st.top->next;
Node* copy = top;
while (original != nullptr) {
// Add a node to the copy
copy->next = new Node(original->data);
original = original->next;
copy = copy->next;
}
}
}
// Frees dynamic memory associated with calling object
void Stack::deleteStack()
{
Node* temp = top;
while (top != nullptr) {
top = top->next;
delete temp;
temp = top;
}
}
// Add a value to the top of the stack
// NOTE: does not have a max size
void Stack::push(int val)
{
// Should throw a bad_alloc exception if memory cannot be allocated
/*
if (top + 1 == capacity) {
throw out_of_range("Stack is full.");
}
*/
// Stack is empty
if (top == nullptr) {
top = new Node(val, nullptr);
}
// Stack is non-empty
else {
// old list: top -> 3 -> 2 -> 1
// push 4
Node* newNode = new Node(val, top);
// newNode -> 4 -> 3 -> 2 -> 1
top = newNode;
// top -> 4 -> 3 -> 2 -> 1
}
}
// Remove and return the value at the top of the stack
int Stack::pop()
{
if (empty()) {
throw out_of_range("Stack is empty.");
}
int result = top->data;
Node* temp = top;
top = top->next;
delete temp;
return result;
}
// Return the value at the top of the stack
int Stack::peek() const
{
if (empty()) {
throw out_of_range("Stack is empty.");
}
return top->data;
}
// Return true if the stack is empty
bool Stack::empty() const
{
return top == nullptr;
}
// Prints the stack
void Stack::print() const
{
printHelper(top);
cout << endl;
}
// Recursive helper function to print stack from top to bottom
void Stack::printHelper(Node* nd) const
{
if (nd != nullptr) {
// Note - swapping these two lines prints the stack from bottom to
top
cout << nd->data << " ";
printHelper(nd->next); // Recursive call
}
}
// Iterative helper function to print stack
//void Stack::printHelper()
//{
// Node* temp = top;
// while (temp != nullptr) {
// cout << temp->data << " ";
// temp = temp->next;
// }
//}
/* Array Implementation
// Default constructor to create an empty stack of size 10
Stack::Stack()
{
capacity = 10;
arr = new int[capacity];
top = -1;
}
// Constructor to creat an empty stack of size n
Stack::Stack(int n)
{
capacity = n;
arr = new int[capacity];
top = -1;
}
// Add a value to the top of the stack
// TO DO: handle errors when the stack is full
void Stack::push(int val)
{
if (top + 1 == capacity) {
throw out_of_range("Stack is full.");
}
arr[++top] = val;
}
// Remove and return the value at the top of the stack
// TO DO: handle errors when the stack is empty
int Stack::pop()
{
if(empty()){
throw out_of_range("Stack is empty.");
}
//top--;
//return arr[top+1];
return arr[top--];
}
// Return the value at the top of the stack
// TO DO: handle errors when the stack is empty
int Stack::peek()
{
if (empty()) {
throw out_of_range("Stack is empty.");
}
return arr[top];
}
// Return true if the stack is empty
bool Stack::empty()
{
return top == -1;
}
// Prints the stack
void Stack::print()
{
for (int i = 0; i <= top; i++) {
cout << arr[i] << " ";
}
cout << endl;
}
*/
