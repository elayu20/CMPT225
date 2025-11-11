#include "Wordlist.h"
#include <cassert>
#include <functional>
#include <iostream>
using namespace std;

void divider(const string& label) {
    cout << "\n==================== " << label << " ====================\n";
}

// Helper integrity check — optional debug only
bool isBalanced(Wordlist& wl, AVLTreeNode* node) {
    if (!node) return true;
    int balance = abs(wl.getHeight(node->left) - wl.getHeight(node->right));
    if (balance > 1) {
        cout << "Unbalanced at: " << node->word << " (balance=" << balance << ")\n";
        return false;
    }
    return isBalanced(wl, node->left) && isBalanced(wl, node->right);
}

void testAllFunctions() {
    divider("Insert and getCount / contains");

    Wordlist wl;
    wl.insert("apple");
    wl.insert("banana");
    wl.insert("apple");  // duplicate
    wl.insert("carrot");

    // Basic verification
    cout << "Contains apple? " << wl.contains("apple") << endl;
    cout << "Count of apple: " << wl.getCount("apple") << endl;
    cout << "Contains grape? " << wl.contains("grape") << endl;
    cout << "Total words: " << wl.totalWords() << " (expected 4)" << endl;
    cout << "Different words: " << wl.differentWords() << " (expected 3)" << endl;

    divider("Most frequent and singletons");
    cout << "Most frequent: " << wl.mostFrequent() << endl;
    cout << "Singletons: " << wl.singletons() << endl;

    divider("Copy constructor and operator=");
    Wordlist wlCopy(wl);  // deep copy
    wlCopy.insert("date");
    cout << "Copy has 'date': " << wlCopy.contains("date") << endl;
    cout << "Original has 'date': " << wl.contains("date") << endl;

    Wordlist wlAssign;
    wlAssign = wl;  // test operator=
    wlAssign.insert("egg");
    cout << "Assign has 'egg': " << wlAssign.contains("egg") << endl;
    cout << "Original has 'egg': " << wl.contains("egg") << endl;

    divider("Remove nodes");
    wl.insert("fig");
    wl.insert("grape");
    wl.insert("honey");
    wl.insert("grape");
    wl.insert("grape");

    cout << "Before removal:\n";
    wl.printWords();

    cout << "\nRemoving 'banana' (leaf or single)... " << wl.remove("banana") << endl;
    cout << "Removing 'apple' (multi-count)... " << wl.remove("apple") << endl;
    cout << "Removing 'fig' (leaf)... " << wl.remove("fig") << endl;

    wl.printStatistics();
    wl.printWords();

    divider("Destructor coverage test (implicit)");
    {
        Wordlist temp;
        temp.insert("x");
        temp.insert("y");
        temp.insert("z");
        temp.printWords();
    } // destructor auto-called here

    divider("AVL balance check (debug only)");
    assert(isBalanced(wl, wl.getRoot()) && "AVL tree not balanced after operations!");
}

void testFileConstructor() {
    divider("File constructor - tiny_shakespeare.txt");
    Wordlist wl("tiny_shakespeare.txt");

    wl.printStatistics();

    cout << "\nFirst 20 words in order (sorted):\n";
    int counter = 0;
    std::function<void(AVLTreeNode*)> limitedPrint = [&](AVLTreeNode* node) {
        if (node == nullptr || counter >= 20) return;
        limitedPrint(node->left);
        if (counter < 20) {
            cout << node->word << " " << node->count << endl;
            counter++;
        }
        limitedPrint(node->right);
    };
    limitedPrint(wl.getRoot());
}

int main() {
    testAllFunctions();
    testFileConstructor();

    cout << "\nAll tests completed successfully.\n";
    return 0;
}

