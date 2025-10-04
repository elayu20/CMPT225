test: StringListTest.cpp StringList.cpp
	g++ -fsanitize=address StringListTest.cpp StringList.cpp -o test

main: StringList.cpp main.cpp
	g++ -fsanitize=address StringList.cpp main.cpp -o main

testDriver: test.cpp
	g++ -fsanitize=address StringList.cpp test.cpp -o testDriver

clean:
	rm -f *.o test main testDriver
