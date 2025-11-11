#include "Wordlist.h"

int main() {
	Wordlist wl;

	wl.insert("dog");
	wl.insert("cat");
	wl.insert("cat");
	wl.insert("bat");
	wl.insert("cow");
	wl.insert("cow");
	wl.insert("cow");
	wl.insert("bat");

	wl.printStatistics();
	wl.printWords();

	if(wl.remove("cat") == true) {
		printf("Remove successful!\n");
	}
	else printf("Unsuccessful remove.\n");

	wl.printStatistics();
	wl.printWords();

	return 0;
}
