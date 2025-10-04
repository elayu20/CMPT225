#include <iostream>
#include <string>
#include "StringList.h"

using std::string;
using std::cout;
using std::endl;

int main(void) {
	cout << "Initializing lists" << endl;
	StringList lst1;

	lst1.insertFront("tree");
	lst1.insertFront("cat");
	lst1.insertFront("dog");
	lst1.print();
	lst1.debugUndoStack();

	cout << "calling removeAll()" << endl;
	lst1.removeAll();
	lst1.print();
	lst1.debugUndoStack();

	cout << "Calling undo" << endl;
	lst1.undo();
	lst1.print();
	lst1.debugUndoStack();

	cout << "Calling undo" << endl;
	lst1.undo();
	lst1.print();
	lst1.debugUndoStack();

	cout << "Calling undo" << endl;
	lst1.undo();
	lst1.print();
	lst1.debugUndoStack();
}
