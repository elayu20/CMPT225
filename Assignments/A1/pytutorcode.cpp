#include <string>
#include<stdexcept>
#include <iostream>

using std::out_of_range;
using std::runtime_error;

class Song
{
public:
    // Constructor
    Song(int len)
{
  length = len;
}

private:
    int length;
};

class PlayListNode {
public:
    Song song; //data representing a song
    PlayListNode* next; //pointer to next node in list

    // Constructors

    // PARAM: sng = song data, nxt = pointer to next node
    // POST: Sets song to sng and next to nxt
    PlayListNode(Song sng, PlayListNode* nxt) : song(sng), next(nxt) {}

    // PARAM: sng = song data
    // POST: Sets song to sng and next to nullptr
    PlayListNode(Song sng) : song(sng), next(nullptr) {}

};

class PlayList {
public:
    PlayList() {
      head = nullptr;
      numSongs = 0;
    }
    
    ~PlayList() {
    }
    
    void insert(Song sng, unsigned int pos) {
      if (numSongs == 0) { // For empty playlists
        PlayListNode* newSong = new PlayListNode(sng);
        head = newSong;
    }

    else if (pos == 0) { // To insert at beginning on a non-empty list
        PlayListNode* newSong = new PlayListNode(sng, head);
        head = newSong;
    }
    
    else if (pos > 0 && pos < numSongs) { // To insert at the end or middle
        PlayListNode* currentNode = head;

        for (unsigned int i = 0; i < pos - 1; i++) {
            currentNode = currentNode->next;
        }

        PlayListNode* newSong = new PlayListNode(sng, currentNode->next);
        currentNode->next = newSong;
    }

    else {
        std::cout << "Insert position out of bounds!" << std::endl;
    }

    numSongs++;
    return;
    }
    
private:
    PlayListNode* head;
    unsigned int numSongs;
};

int main (void) {
  PlayList* myPlayList = new PlayList();
  
  Song song1(225);
  Song song2(185);
  Song song3(321);
  Song song4(281);
  
  myPlayList->insert(song1, 0);
  myPlayList->insert(song2, 2);
  myPlayList->insert(song3, 0);
  myPlayList->insert(song4, 3);
}
