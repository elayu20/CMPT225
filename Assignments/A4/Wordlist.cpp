#include "Wordlist.h"
#include <iomanip>
using std::setprecision;
using std::fixed;

// Default constructor
// Creates an empty Wordlist (root is null pointer)
Wordlist::Wordlist()
	: root(nullptr), differentWordCount(0), totalWordCount(0)
{}

// File Constructor
Wordlist::Wordlist(string file)
	: root(nullptr), differentWordCount(0), totalWordCount(0)
{
	ifstream myFile;
	myFile.open(file);

	string next;
	while (myFile >> next) { // Stop when read fails
		insert(next);
	}

	myFile.close();
}

void Wordlist::copyPreOrder(AVLTreeNode* node) {
	if (node == nullptr) {
		return;
	}

	// Insert the word as many times as it appeared
	for (unsigned int i = 0; i < node->count; i++) {
		insert(node->word);
	}
	copyPreOrder(node->left);
	copyPreOrder(node->right);
}
// Copy constructor
Wordlist::Wordlist(const Wordlist& lst)
	: root(nullptr), differentWordCount(0), totalWordCount(0)
{
	copyPreOrder(lst.getRoot());
}

// Operator=
Wordlist& Wordlist::operator=(const Wordlist& lst) {
	if (&lst != this) {
		// Delete current tree and reset attributes
		deletePostOrder(root);
		root = nullptr;
		differentWordCount = 0;
		totalWordCount = 0;

		copyPreOrder(lst.getRoot());
	
	}

	return *this;
}

// Helper function
void Wordlist::deletePostOrder(AVLTreeNode* node) {
	// left->right->visit
	if (node == nullptr) {
		return;
	}
	deletePostOrder(node->left);
	deletePostOrder(node->right);

	delete node;
}
// Destructor
Wordlist::~Wordlist() {
	deletePostOrder(root);
	root = nullptr;
	differentWordCount = 0;
	totalWordCount = 0;
}

// Recursive AVL insertion
// If word does not exist, insert with count 1
// If word exists, increment its count
// Returns the new root of the subtree after balancing
AVLTreeNode* Wordlist::insertAVL(AVLTreeNode* node, const string& word) {
	// Base case - empty node
	if (node == nullptr) {
		differentWordCount++;
		totalWordCount++;
		return new AVLTreeNode(word);
	}

	// Traversing through tree recursively
	if (word < node->word) {
		node->left = insertAVL(node->left, word);
		node->left->parent = node;
	}
	else if (word > node->word) {
		node->right = insertAVL(node->right, word);
		node->right->parent = node;
	}
	else {
		// Word already exists, increment count
		node->count++;
		totalWordCount++;
		return node;
	}

	// Rebalance current subtree
	return rebalance(node);
}
// Calls recursive insert and rebalances tree
void Wordlist::insert(string word) {	
	root = insertAVL(root, word);
}

// Recursive AVL remove helper
// Removes the word and rebalances the subtree
// Returns true if successful
AVLTreeNode* Wordlist::removeAVL(AVLTreeNode* node, const string& word, bool& removed) {
	// Word not found
	if (node == nullptr) {
		return node;
	}

	// Traversing through tree recursively
	if (word < node->word) {
		node->left = removeAVL(node->left, word, removed);
		if (node->left != nullptr) node->left->parent = node;
	}
	else if (word > node->word) {
		node->right = removeAVL(node->right, word, removed);
		if (node->right != nullptr) node->right->parent = node;
	}
	else {
		// Found the node to remove
		removed = true;
		totalWordCount -= node->count;
		differentWordCount--;

		// Case 1: No children
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			return nullptr;
		}
		// Case 2: One child
		else if (node->left == nullptr) { 
			AVLTreeNode* temp = node->right;
			temp->parent = node->parent;
			delete node;
			return temp;
		}
		else if (node->right == nullptr) { 
			AVLTreeNode* temp = node->left;
			temp->parent = node->parent;
			delete node;
			return temp;
		}
		// Case 3: Two children
		// Using predecessor
		else {
			AVLTreeNode* predecessor = node->left;
			while (predecessor->right != nullptr) {
				predecessor = predecessor->right;
			}
			// Copy predecessor's data into this node
			node->word = predecessor->word;
			node->count = predecessor->count;
			// Remove the predecessor node
			node->left = removeAVL(node->left, predecessor->word, removed);
			if (node->left != nullptr) node->left->parent = node;
		}
	}

	// If the tree had only one node, return it
	if (node == nullptr) return node;

	// Rebalance this node;
	return rebalance(node);
}
bool Wordlist::remove(string word) {
	bool removed = false;
	root = removeAVL(root, word, removed);
	return removed;
}

// Returns count of string word parameter
int Wordlist::getCount(string word) const {
	AVLTreeNode* current = root;

	while (current != nullptr) {
		if (word == current->word) {
			return current->count;
		}
		// In left subtree if current word is larger
		else if (word < current->word) {
			current = current->left;
		}
		// In right subtree if current word is smaller
		else {
			current = current->right;
		}
	}

	return 0;
}

// Returns true if string parameter is in word list, otherwise false
bool Wordlist::contains(string word) const {
	AVLTreeNode* current = root;

	while (current != nullptr) {
		if (word == current->word) {
			return true;
		}
		// In left subtree if current word is larger
		else if (word < current->word) {
			current = current->left;
		}
		// In right subtree if current word is smaller
		else {
			current = current->right;
		}
	}

	return false;
}

int Wordlist::differentWords() const {
	return differentWordCount;
}

int Wordlist::totalWords() const {
	return totalWordCount;
}

void Wordlist::mostFrequentPostOrder(AVLTreeNode* node, string &maxWord, int &maxCount) const{
	if (node == nullptr) {
		return;
	}
	mostFrequentPostOrder(node->left, maxWord, maxCount);
	mostFrequentPostOrder(node->right, maxWord, maxCount);

	if (node->count > maxCount || node->count == maxCount && node->word < maxWord) {
		maxWord = node->word;
		maxCount = node->count;
	}
}
string Wordlist::mostFrequent() const {
	if (root == nullptr) {
		throw std::invalid_argument("Word list is empty.");
	}

	string maxWord = "";
	int maxCount = 0;

	mostFrequentPostOrder(root, maxWord, maxCount);

	// Returns the word and its count
	return maxWord + " " + std::to_string(maxCount);
}

void Wordlist::singletonsPostOrder(AVLTreeNode* node, int &singletons) const {
	if (node == nullptr) {
		return;
	}
	singletonsPostOrder(node->left, singletons);
	singletonsPostOrder(node->right, singletons);

	if (node->count == 1) {
		singletons += 1;
	}
}
int Wordlist::singletons() const {
	int singletons = 0;
	singletonsPostOrder(root, singletons);
	return singletons;
}

// Prints useful statistics about the word list
void Wordlist::printStatistics() const
{
	cout << "Number of different words: " << differentWords() << endl;
	cout << "    Total number of words: " << totalWords() << endl;
	cout << "       Most frequent word: " << mostFrequent() << endl;
	cout << "     Number of singletons: " << singletons()
		<< setprecision(0) << fixed
		<< " (" << 100.0 * singletons() / differentWords() << "%)"
		<< endl;
}

void Wordlist::printWordsInOrder(AVLTreeNode* node) const {
	if (node == nullptr) {
		return;
	}
	printWordsInOrder(node->left);	
	cout << node->word << " " << node->count << endl;
	printWordsInOrder(node->right);
}
void Wordlist::printWords() const {
	printWordsInOrder(root);
}

int Wordlist::getHeight(AVLTreeNode* node) {
	if (node == nullptr) {
		return -1;
	}
	return node->height;
}
 
int Wordlist::getBalance(AVLTreeNode* node) {
	if (node == nullptr) {
		return 0;
	}
	return getHeight(node->left) - getHeight(node->right);
}

void Wordlist::updateHeight(AVLTreeNode* node) {
	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);

	if (leftHeight > rightHeight) node->height = leftHeight + 1;
	else node->height = rightHeight + 1;
}

// Performs a left rotation and returns the new subtree root
AVLTreeNode* Wordlist::rotateLeft(AVLTreeNode* x) { // x is node to be rotated
	if (x == nullptr || x->right == nullptr) return x;

	AVLTreeNode* y = x->right;
	x->right = y->left;

	// Set nodes' parent references
	// y's left child
	if (y->left != nullptr) {
		y->left->parent = x;
	}

	// y
	y->parent = x->parent;

	// Set child reference of x's parent
	if (x->parent == nullptr) root = y; // x was root
	else if (x == x->parent->left) x->parent->left = y; // left child
	else x->parent->right = y;

	// Make x y's left child
	y->left = x;
	x->parent = y;

	// Update heights
	updateHeight(x);
	updateHeight(y);
	
	// Return new root of this rotated subtree
	return y;
}

// Performs a right rotation and returns the new subtree root
AVLTreeNode* Wordlist::rotateRight(AVLTreeNode* x) { // x is node to be rotated
	if (x == nullptr || x->left == nullptr) return x;

	AVLTreeNode* y = x->left;
	x->left = y->right;

	// Set nodes' parent references
	// y's left child
	if (y->right != nullptr) {
		y->right->parent = x;
	}

	// y
	y->parent = x->parent;

	// Set child reference of x's parent
	if (x->parent == nullptr) root = y; // x was root
	else if (x == x->parent->left) x->parent->left = y; // left child
	else x->parent->right = y;

	// Make x y's right child
	y->right = x;
	x->parent = y;

	// Update heights
	updateHeight(x);
	updateHeight(y);
	
	// Return new root of this rotated subtree
	return y;
}

// Balances the subtree which has node root
// Returns pointer to new root of subtree after rotation
AVLTreeNode* Wordlist::rebalance(AVLTreeNode* node) {
	if (node == nullptr) return node;

	updateHeight(node);
	int balance = getBalance(node);

	// Left heavy
	if (balance > 1) {
		// Left-Right case
		if (getBalance(node->left) < 0) {
			node->left = rotateLeft(node->left);
		}
		return rotateRight(node);
	}
	// Right heavy
	if (balance < -1) {
		// Right-Left case
		if (getBalance(node->right) > 0) {
			node->right = rotateRight(node->right);
		}
		return rotateLeft(node);
	}

	// Balanced
	return node;
}
