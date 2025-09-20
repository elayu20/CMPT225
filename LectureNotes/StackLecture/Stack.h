#pragma once
// Simple node class for linked list
class Node
{
public:
int data;
Node* next;
Node(int val, Node* nd = nullptr) : data(val), next(nd) {};
//: etc. - initializer list
};
class Stack
{
public:
// Public Interface
// Default constructor to create an empty stack of size 10
Stack();
// Constructor to create an empty stack of size n
Stack(int n);
// Copy constructor
// Required (with destructor and overloaded op=) if class allocates
// space in dynamic memory with new (or malloc, alloc, etc.)
// Used to copy objects that are passed to functions by value
Stack(const Stack& st);
// Destructor (frees up dynamic memory) associated with object
// i.e. calls delete on nodes created using new
~Stack();
// Overloaded assignment operator
// Used to assign objects returned from a function
Stack& operator=(const Stack& st);
// Add a value to the top of the stack
// PARAM: val - value to be inserted into stack
// POST: val inserted at the top of the stack
void push(int val);
// Remove and return the value at the top of the stack
// PRE: Stack is non-empty
// POST: top of the stack is removed and returned
int pop();
// Returns the value at the top of the stack
// PRE: Stack is non-empty
// POST: top of the stack is returned
int peek() const;
// POST: Returns true if the stack is empty
bool empty() const;
// POST: Prints contents of stack from top to bottom
void print() const;
private:
// Linked List Implementation
Node* top;
// Helper function to print stack
// PARAM:
// POST: Prints contents of stack from nd to bottom
void printHelper(Node* nd) const;
// Helper function to copy stack
// PARAM: st is stack to be copied
// POST: Makes calling object a new stack containing the contents of st
void copyHelper(const Stack& st);
// Helper function to delete stack
// POST: Frees dynamic memory associate with (nodes of) calling objecct
void deleteStack();
/* Array Implementation
int* arr;
int top;
int capacity;
*/
};
