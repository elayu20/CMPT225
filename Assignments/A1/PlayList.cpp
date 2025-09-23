// Edward Alayu
// September 20, 2025
#include "PlayList.h"
#include <iostream>

using std::cout;
using std::endl;
using std::out_of_range;

// PlayList method implementations go here
PlayList::PlayList() {
	head = nullptr;
	numSongs = 0;
}

PlayList::PlayList(const PlayList &pl) {
	if (pl.head == nullptr) {
		head = nullptr;
	}
	else {
		head = new PlayListNode(pl.head->song); // Copies PlayList's head into its own, new linked list
		PlayListNode* currentOriginal = pl.head->next;
		PlayListNode* currentCopy = head;

		// Pointer for original list is one ahead of pointer for copy list
		// Assigns current copies' next to a new node that is created by copying current original's song
		// Move up the list, current original is still one node ahead of current copy
		while (currentOriginal != nullptr) {
			currentCopy->next = new PlayListNode(currentOriginal->song);
			currentCopy = currentCopy->next;
			currentOriginal = currentOriginal->next;
		}
	}
	numSongs = pl.numSongs;
}

PlayList::~PlayList() {
	PlayListNode* currentNode;
	PlayListNode* nextNode;

	while (head != nullptr) {
		currentNode = head;
		nextNode = currentNode->next;
		delete currentNode;
		head = nextNode;
	}
	numSongs = 0;
	head = nullptr;
}

PlayList& PlayList::operator=(const PlayList & pl) {
	if (&pl != this) {
		this->~PlayList();

		if (pl.head == nullptr) {
			head = nullptr;
		}
		else {
			head = new PlayListNode(pl.head->song); // Copies PlayList's head into its own, new linked list
			PlayListNode* currentOriginal = pl.head->next;
			PlayListNode* currentCopy = head;

			// Pointer for original list is one ahead of pointer for copy list
			// Assigns current copies' next to a new node that is created by copying current original's song
			// Move up the list, current original is still one node ahead of current copy
			while (currentOriginal != nullptr) {
				currentCopy->next = new PlayListNode(currentOriginal->song);
				currentCopy = currentCopy->next;
				currentOriginal = currentOriginal->next;
			}
		}
		numSongs = pl.numSongs;
	}
	return *this;
}

void PlayList::insert(Song sng, unsigned int pos) {
	
	if (numSongs == 0) { // For empty playlists
		PlayListNode* newSong = new PlayListNode(sng);
		head = newSong;
	}

	else if (pos == 0) { // To insert at beginning on a non-empty list
		PlayListNode* newSong = new PlayListNode(sng, head);
		head = newSong;
	}
	
	else if (pos > 0 && pos <= numSongs) { // To insert at the end or middle
		PlayListNode* currentNode = head;

		for (unsigned int i = 0; i < pos - 1; i++) {
			currentNode = currentNode->next;
		}

		PlayListNode* newSong = new PlayListNode(sng, currentNode->next);
		currentNode->next = newSong;
	}

	else { // Out of bounds position
		cout << "Insert position out of bounds!" << endl;
		return; // Exit function without incrementing numSongs
	}

	numSongs++;
}

Song PlayList::remove(unsigned int pos) {
	Song songToReturn("Invalid", "None", 1); // Default Value
				
	if (numSongs < 1) {
		throw out_of_range("Can't remove from empty play list!");
	}

	PlayListNode* nodeToRemove; // Node to remove and return the song
	PlayListNode* previousNode = head; // Node before nodeToRemove
	
	if (pos == 0) {
		nodeToRemove = head;
		head = head->next;
		songToReturn = nodeToRemove->song;
		delete nodeToRemove;
	}
	else if (pos <= numSongs - 1) { 

		for (unsigned int i = 0; i < pos - 1; i++) { // Assign previousNode to node before nodeToRemove
			previousNode = previousNode->next;
		}

		nodeToRemove = previousNode->next;
		previousNode->next = nodeToRemove->next;
		songToReturn = nodeToRemove->song;
		delete nodeToRemove;
	}	
	else { // For out of bounds position
	       throw out_of_range("Position out of bounds!");
	}	

	
	numSongs--;
	return songToReturn;
}

void PlayList::swap(unsigned int pos1, unsigned int pos2) {

	if (pos1 >= 0 && pos1 < numSongs && pos2 >= 0 && pos2 < numSongs) {
		PlayListNode* firstPositionNode = head;
		PlayListNode* secondPositionNode = head;

		for (unsigned int i = 0; i < pos1; i++) { // Assigns to pos1's node
			firstPositionNode = firstPositionNode->next;
		}
		Song tempSong = firstPositionNode->song; // Keep original data of firstPositionNode before swap happens 

		for (unsigned int i = 0; i < pos2; i++) { // Assigns to pos2's node
			secondPositionNode = secondPositionNode->next;
		}

		firstPositionNode->song = secondPositionNode->song;
		secondPositionNode->song = tempSong;
	}
	else { // Out of bounds positions
		cout << "Swap positions out of bounds!" << endl;
	}
}

Song PlayList::get(unsigned int pos) const {
	if (numSongs < 1) {
		throw out_of_range("Empty playlist!");
	}

	if (pos >= numSongs) {
		throw  out_of_range("Return position out of bounds!");
	}

	// Already covered pos <= numSongs - 1, no need for pos >= 0 because unsigned int paramater value
	PlayListNode* currentNode = head;
	for (unsigned int i = 0; i < pos; i++) {
		currentNode = currentNode->next;
	}

	Song songToReturn = currentNode->song;
	return songToReturn;
}

unsigned int PlayList::size() const {
	 return numSongs;
}
