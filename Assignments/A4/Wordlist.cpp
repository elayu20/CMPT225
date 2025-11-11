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

// If word does not exist in list, insert with a count of one
// If word exists in list, increment word's count
void Wordlist::insert(string word) {
	// Empty tree
	if (root == nullptr) {
		root = new AVLTreeNode(word);
		differentWordCount++;
		totalWordCount++;
		return;
	}

	AVLTreeNode* current = root;
	AVLTreeNode* parent;
	int newNodeHeight = 0;
	// Keeps track of which child search ended at on NULL
	// 1 if left, 2 if right
	int whichChild;

	// Traversing through tree, just checking if word exists
	while (current != nullptr) {
		// Word already exists, increment and stop
		if (word == current->word) {
			totalWordCount++;
			current->count++;
			return;
		}
		else if (word < current->word) {
			parent = current;
			current = current->left;
			whichChild = 1;
		}
		else {
			parent = current;
			current = current->right;
			whichChild = 2;
		}
		newNodeHeight++;
	}
	differentWordCount++;
	totalWordCount++;

	// Word doesn't exist, create new node
	AVLTreeNode *newNode = new AVLTreeNode(word);
	newNode->height = newNodeHeight;
	newNode->parent = parent;

	if (whichChild == 1) {
		parent->left = newNode;
	}
	else if (whichChild == 2) {
		parent->right = newNode;
	}
}

// Remove method, returns true if successful
bool Wordlist::remove(string word) {
	// Empty tree
	if (root == nullptr) {
		return false;
	}

	AVLTreeNode* current = root;
	AVLTreeNode* parent = nullptr;

	// Keeps track of which child search ended at when found
	// 1 if left, 2 if right
	int whichChild;
	// Keeps track how many chidlren a node has
	int childrenCount;

	while (current->word != word && current != nullptr) {

		// Traversing through
		if (word < current->word) {
			parent = current;
			current = parent->left;
			whichChild = 1;
		}
		else if (word > current->word) {
			parent = current;
			current = parent->right;
			whichChild = 2;
		}
	}

	// Didn't find word
	if (current == nullptr) {
		return false;
	}

	// Found word

	// Determining how many children
	// 2 children
	if (current->left != nullptr && current->right != nullptr) {
		childrenCount = 2;
	}
	// 1 child
	else if (current->left != nullptr || current->right != nullptr) {
		childrenCount = 1;
	}
	// No child
	else {
		childrenCount = 0;
	}

	// Only update differentWords if the count is 1
	if (current->count == 1) {
		totalWordCount--;
		differentWordCount--;
	}
	else {
		totalWordCount--;
	}

	// No children, remove the leaf
	if (childrenCount == 0) {	
		// Update parent
		if (whichChild == 1) parent->left = nullptr;
		else if (whichChild == 2) parent->right = nullptr;

		delete(current);

		if (root->word == word) root = nullptr;
	}
	// 1 child
	else if (childrenCount == 1) {
		// Root, whichChild not assigned
		if (root->word == word) {
		}
		if (whichChild == 1) {
			parent = current->left;
		}
		else if (whichChild == 2) {
			parent = current->right;
		}
	}

	return true;
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
	if (root == nullptr) {
		throw std::invalid_argument("Word list is empty.");
	}
	printWordsInOrder(root);
}
