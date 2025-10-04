#include "StringList.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        cout << "=== Testing StringList ===\n";

        StringList list;

        // --- Basic insert tests ---
        cout << "\nInserting elements...\n";
        list.insertBack("Apple");
        list.insertBack("Banana");
        list.insertBack("Cherry");
        list.print(); // { Apple Banana Cherry }

        // --- Undo insertBack ---
        cout << "Undo last insertBack:\n";
        list.undo();
        list.print(); // { Apple Banana }

        // --- insertFront ---
        cout << "\nInserting at front...\n";
        list.insertFront("Mango");
        list.print(); // { Mango Apple Banana }

        cout << "Undo insertFront:\n";
        list.undo();
        list.print(); // { Apple Banana }

        // --- insertBefore ---
        cout << "\nInserting before index 1...\n";
        list.insertBefore(1, "Grape");
        list.print(); // { Apple Grape Banana }

        cout << "Undo insertBefore:\n";
        list.undo();
        list.print(); // { Apple Banana }

        // --- set() ---
        cout << "\nSetting index 1 to Kiwi...\n";
        list.set(1, "Kiwi");
        list.print(); // { Apple Kiwi }

        cout << "Undo set:\n";
        list.undo();
        list.print(); // { Apple Banana }

        // --- remove() ---
        cout << "\nRemoving index 0 (Apple)...\n";
        list.remove(0);
        list.print(); // { Banana }

        cout << "Undo remove:\n";
        list.undo();
        list.print(); // { Apple Banana }

        // --- removeAll() ---
        cout << "\nRemoving all elements...\n";
        list.removeAll();
        list.print(); // { }

        cout << "Undo removeAll:\n";
        list.undo();
        list.print(); // { Apple Banana }

        // --- Assignment operator ---
        cout << "\nTesting overloaded assignment...\n";
        StringList other;
        other.insertBack("Tomato");
        other.insertBack("Lime");
        other.insertBack("Melon");

        list = other;
        list.print(); // { Tomato Lime Melon }

        cout << "Undo assignment:\n";
        list.undo();
        list.print(); // { Apple Banana }

        // --- Copy constructor ---
        cout << "\nTesting copy constructor...\n";
        StringList copy(list);
        cout << "Copied list: ";
        copy.print();

        // --- Comparison operators ---
        cout << "\nComparing list and copy: "
             << (list == copy ? "Equal" : "Not equal") << endl;

        copy.set(1, "Blueberry");
        cout << "After changing copy: "
             << (list == copy ? "Equal" : "Not equal") << endl;

        // --- Exception handling ---
        cout << "\nTrying invalid index access...\n";
        try {
            list.get(10);
        } catch (out_of_range &e) {
            cout << "Caught exception: " << e.what() << endl;
        }

        cout << "\nTrying undo on empty stack...\n";
        list.removeAll();
        list.undo(); // Undo removeAll
        try {
            list.undo(); // Nothing left to undo
        } catch (out_of_range &e) {
            cout << "Caught exception: " << e.what() << endl;
        }

        cout << "\n=== All tests completed ===\n";

    } catch (const exception& e) {
        cerr << "Unexpected exception: " << e.what() << endl;
    }
}

