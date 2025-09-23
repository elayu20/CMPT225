#include <iostream>
#include "Stack.h"

using std::cout;
using std::endl;

class Stack {
public:
	// Constructor and destructors
	// Stack::Stack - fully qualified name

	// Default stack of size  10
	Stack::Stack () {
		capacity = 10;
		arr = new int[capacity];
		top = -1;
	}

	Stack::Stack (int sz) {
		capacity = sz;
		arr = new int[capacity];
		top = -1;
	}

	void Stack::push(int value) {
		top++;
		arr[top] = value;
	}

	int Stack::pop(){ 
		return arr[top--];	
	}

	int Stack::peek(){
		return arr[top];
	}

	// Return number of elemnts in stack
	int Stack::size(){
		return top + 1;
	}

	// returns true iff stack is empty
	bool Stack::empty() {
		return top == -1;
	}

	// prints contenst of the stack
	void Stack::print() {
		for(int i = 0; i <= top; i++) {
			cout << arr[i] << endl;
		}
	}
	
private:
	// Array implementation
	int* arr{
	}
	int top{
	}
	int capacity{
	}
