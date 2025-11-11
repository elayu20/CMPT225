#pragma once
#include <string>
#include <iostream>
#include <fstream> // files
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

class AVLTreeNode {
public:
	AVLTreeNode* parent;
	AVLTreeNode* left;
	AVLTreeNode* right;
	string word;
	int count;
	int height;

	// Constructors ...
	AVLTreeNode(string w)
		: word(w), count(1), parent(nullptr), left(nullptr), right(nullptr), height(0) {}
};

// Wordlist class
class Wordlist
{
private:
	// Class attributes go here
	// Your class MUST have a root node named root (below)
	AVLTreeNode* root; // DO NOT REMOVE

	// Helper attributes for differentWords and totalWords
	int differentWordCount;
	int totalWordCount;

	// Traversal helper methods
	void deletePostOrder(AVLTreeNode* node);
	void mostFrequentPostOrder(AVLTreeNode* node, string &maxWord, int &maxCount) const;
	void singletonsPostOrder(AVLTreeNode* node, int &singletons) const;
	void printWordsInOrder(AVLTreeNode* node) const;
	void copyPreOrder(AVLTreeNode* node);

	// AVL-specific helper methods
	int getHeight(AVLTreeNode* node);
	int getBalance(AVLTreeNode* node);
	void updateHeight(AVLTreeNode* node);
	AVLTreeNode* rotateLeft(AVLTreeNode* x);
	AVLTreeNode* rotateRight(AVLTreeNode* x);
	AVLTreeNode* rebalance(AVLTreeNode* node);
	AVLTreeNode* insertAVL(AVLTreeNode* node, const string& word);
	AVLTreeNode* removeAVL(AVLTreeNode* node, const string& word, bool& removed);
public:
	// public methods go here

	// Default constructor
	Wordlist();

	// File Constructor
	Wordlist(string file);

	// Copy constructor
	Wordlist(const Wordlist& lst);

	// Operator=
	Wordlist& operator=(const Wordlist& lst);

	// Destructor
	~Wordlist();

	// If word does not exist in list, insert with a count of one
	// If word exists in list, increment word's count
	void insert(string word);

	// Remove method, returns true if successful
	bool remove(string word);

	// Returns count of string word parameter
	int getCount(string word) const;

	// Returns true if string parameter is in word list, otherwise false
	bool contains(string word) const;

	int differentWords() const;
	int totalWords() const;
	string mostFrequent() const;
	int singletons() const;

	// Prints useful statistics about the word list
	void printStatistics() const;

	void printWords() const;

	// Returns the root of the AVL tree
	AVLTreeNode* getRoot() const { return root; }; // DO NOT REMOVE
};
