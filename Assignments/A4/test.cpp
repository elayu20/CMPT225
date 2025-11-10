#include "Wordlist.h"

int main() {
	Wordlist wl("tiny_shakespeare.txt");

	Wordlist wl2(wl);

	if (wl2.contains(wl.getRoot()->word) == true) {
		printf("yes it does\n");
	}

	wl.printStatistics();
	wl2.printStatistics();

	return 0;
}
