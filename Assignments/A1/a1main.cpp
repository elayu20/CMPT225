// Edward Alayu
// Class: CMPT 225
// Date: September 22, 2025
// a1main.cpp
//
// Big O Notation worst-case running time
// 
// Default constructor: O(1)
// 	Reasoning - Is performing assignments for head and numSongs, which are constant time
// Destructor: O(n)
// 	Reasoning - Has to go through the whole linked list to delete each node once, where n = number of songs
// Copy constructor: O(n)
// 	Reasoning - Creating the deep copy takes n amount of nodes in time
// Overloaded assignment operator: O(n)
// 	Reasoning - Clearing the existing list with the destructor O(n) and also deep copies O(n), and they run after one another, 
// 		    which is just O(n) + O(n) = O(2n) which is just O(n)
// Insert: O(n)
// 	Reasoning - Its worst case is inserting at the end, which has to traverse through all previous n amount of
// 		   nodes before inserting.
// Remove: O(n)
// 	Reasoning - Its worst case is removing at the end, which has to traverse through n amount of previous nodes before removing
// Get: O(n)
// 	Reasoning - Its worst case is getting the last song, which has to traverse through n amount of songs before getting
// Swap: O(n)
// 	Reasoning - Its worst case is if pos1 or pos2 are at the end, which has to traverse through n amount before swapping
// Size: O(1)
// 	Reasoning - Just returns the amount of songs, which is constant time
// Enter a song: O(n)
// 	Reasoning - The function must use the insert method, where the insert method is O(n) and that is it's worst case scenario
// Remove a song: O(n)
// 	Reasoning - The function must use the remove method, where the remove method is O(n)
// Swap two songs: O(n)
// 	Reasoning - The function must use the swap method, where the swap method is O(n)
// Print all the songs: O(n^2)
// 	Reasoning - The get method is nested inside the for loop, where the loop runs n times, and each loop calls get.
// 		    Therefore we can use O(n) * O(n) = O(n^2)
// 	
#include <iostream>
#include <string>
#include "PlayList.h"
#include "Song.h"

using std::cout;
using std::endl;
using std::cin;

int promptChoice() {
	int userChoice;
	cout << "\nEnter 1 (insert), 2 (remove), 3 (swap), 4 (print), or 5 (quit): ";
	cin >> userChoice;
	return userChoice;
}

int promptInsertPosition(PlayList* userPlayList) {
	unsigned int position;
	
	// Prompt for position to insert in
	cout << "Position (";
	if (userPlayList->size() == 0) { // Match range with size of playlist
		cout << "1): ";
	}
	else {
		cout << "1 to " << userPlayList->size() + 1 << "): ";
	}
	cin >> position;

	// Re-prompt if position out of bounds
	while (position > userPlayList->size() + 1 || position < 1 ) {
		cout << "Please, enter a position in range";
		cout << "Position (";
		if (userPlayList->size() == 0) {
			cout << "1): ";
		}
		else {
			cout << "1 to " << userPlayList->size() + 1 << "): ";
		}
		cin >> position;
	}
	return position;
}

// Very similar to prompt insert, with a few changes
int promptRemovePosition(PlayList* userPlayList) {
	unsigned int position;
	
	// Prompt for position to remove in
	if (userPlayList->size() == 0) { // Match range with size of playlist
		cout << "Empty playlist! Cannot remove." << endl;
	} 
	else {
		if (userPlayList->size() == 1) {
			cout << "Position (1): ";
		}
		else {
			cout << "Position (1 to " << userPlayList->size() << "): ";
		}
		cin >> position;

		// Re-prompt if position out of bounds
		while (position > userPlayList->size() || position < 1) {
			cout << "Please, enter a position in range ";
			
			if (userPlayList->size() == 1) {
				cout << "Position (1): ";
			}
			else {
				cout << "1 to " << userPlayList->size() << "): ";
			}
			cin >> position;
		}

		return position;
	}
	return -1;
}

void promptSwapPosition(PlayList* userPlayList, unsigned int &a, unsigned int &b) {

	// Prompt for position to swap in
	if (userPlayList->size() == 0 || userPlayList->size() == 1) {
		cout << "Not enough songs to swap!" << endl;
	}
	else {
		cout << "Swap song at position (1 to " << userPlayList->size() << "): ";
		cin >> a;
		cout << "with the song at position (1 to " << userPlayList->size() << "): ";
		cin >> b;

		while (a < 1 || userPlayList->size() < a || b < 1 || userPlayList->size() < b) {
			cout << "Please, enter swap positions that are in range" << endl;

			cout << "\nSwap song at position (1 to " << userPlayList->size() << "): ";
			cin >> a;
			cout << "with the song at position (1 to " << userPlayList->size() << "): ";
			cin >> b;	
		}
	}
}

int main(void) {
	int userChoice;
	string songName;
	string artistName;
	unsigned int songLength;
	PlayList* userPlayList = new PlayList();
	unsigned int position;
	unsigned int swapPosA, swapPosB;

	// Menu
	cout << "Menu:\n"
	<< "1 - Enter a song in the play list at a given position\n"
	<< "2 - Remove a song from the play list at a given position\n"
	<< "3 - Swap two songs in the playlist\n"
	<< "4 - Print all the songs in the play list\n5 - Quit\n";
	
	userChoice = promptChoice();

	while (userChoice != 5) {

		if (userChoice < 1 || userChoice > 4) {
			cout << "Please, enter a proper choice" << endl;
		}
		else {
			if (userChoice == 1) {
				// Prompt song info
				// Prompt song name
				cout << "Song name: ";
				cin.ignore();
				getline(cin, songName);

				// Prompt artist name
				cout << "Artist: ";
				getline(cin, artistName);

				// Prompt length of song
				cout << "Length: ";
				cin >> songLength;

				// Create song object
				Song song1(songName, artistName, songLength);

				position = promptInsertPosition(userPlayList);
				userPlayList->insert(song1, position - 1);

				cout << "You entered " << songName
				<< " at position " << position << " in the play list" << endl;
			}
			else if (userChoice == 2) {
				position = promptRemovePosition(userPlayList);
				Song currentSong = userPlayList->get(position - 1);
				if (position != -1) {
					userPlayList->remove(position - 1);
					cout << "You removed " << currentSong.getName() << " from the play list" << endl;
				}
			}
			else if (userChoice == 3) {
				promptSwapPosition(userPlayList, swapPosA, swapPosB);
				userPlayList->swap(swapPosA - 1, swapPosB - 1);
				if (swapPosA == swapPosB) {
					cout << "You swapped a song at the same position! Haha" << endl;
				}
				else {
					cout << "You swapped the songs at positions " << swapPosA << " and " << swapPosB << endl;
				}
			}
			else {
				for (unsigned int i = 0; i < userPlayList->size(); i++) {
					Song currentSong = userPlayList->get(i); // Get the song at position i
					cout << i + 1
					<< " " << currentSong.getName()
					<< " (" << currentSong.getArtist()
					<< ") " << currentSong.getLength() << "s" << endl;
				}
			}
		}
		userChoice = promptChoice();
	}
}
