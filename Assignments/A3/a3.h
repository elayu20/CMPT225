#pragma once
#include <iostream>

using std::cout;
using std::endl;

//*****************************************************************************************
// Simple integer power function: computes base^exp
int pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

// Returns a string of 'count' copies of character 'ch'
std::string string(int count, char ch) {
    return std::string(count, ch);
}
//*******************************************************************************************/

// PARAM: arr is array to print the Cartesian product of, n is size of arr
void cartesianProduct(int arr[], int n, int &ops) {
	int i = 0;
	ops = 1; // initialization of i

	while (i < n) { // 1 op per iteration + 1 termination
		ops++; // comparison for i < n

		int j = 0; 
		ops++; // set j to 0

		while (j < n) { // 1 op per iteration + 1 termination
			ops++; // comparison for j < n

			cout << "{" << arr[i] << "," << arr[j] << "}"; 
			j++; 
			cout << " "; 
			ops += 3; // print pair of arrays, increment j, print space
		}
		ops++; // terminating inner while loop

		cout << endl; 
		i++; 
		ops += 2; // printing newline and incrementing i
	}
	ops++; // terminating outer while loop
}

void triangle(int x, int &ops) {
	int i = 0;
	ops = 1; // initialization of i

	while (i < x) { // 1 op per iteration + 1 termination
		ops++; // comparison for i < x

		int j = 0;
		ops++; // set j to 0

		while (j <= i) { // 1 op per iteration + 1 termination
			ops++; // comparison for j <= i

			cout << j << " ";
			j++;
			ops += 2; // printing j and incrementing j
		}
		ops++; // terminating inner while comparison

		cout << endl;
		i++;
		ops += 2; // printing newline and incrementing i
	}
	ops++; // terminating outer while comparison

	while (i > 0) { // 1 op per iteration + 1 termination
		ops++; // comparison for i > 0

		i--;
		int j = 0;
		ops += 2; // decrementing i and set j to 0

		while (j <= i) { // 1 op per iteration + 1 termination
			ops++; // comparison for j <= 1

			cout << j << " ";
			j++;
			ops += 2; // printing j and incrementing j
		}
		ops++; // terminating inner while comparison

		cout << endl;
		ops++; // printing newline
	}
	ops++; // terminating outer while comparison
}

// Returns the index of a 1d array representing a matrix
// given row (r) and column (c) values
// rcIndex costs 1 operation, but will not be counting its ops because manually counting in matrixSelfMultiply
int rcIndex(int r, int c, int columns) {
	return r * columns + c; // return statement includes other operations, so its cost is 1
}

// PRE: m represents a square matrix of size rows * rows
// PARAM: rows represents the number of both rows and columns
// POST: Returns a pointer to an array (matrix) of the same size as m
// NOTE: values are indexed r0c0,r0c1,…,r0cn-1,r1c0,…
int* matrixSelfMultiply(int* m, int rows, int &ops) {
	// Create result array
	int columns = rows;
	int* result = new int[rows * columns];
	int r = 0;
	ops = 3; // initializing columns, result pointer, and r
	
	while (r < rows) { // 1 operation + 1 termination
		ops++; // for comparison r < rows

		int c = 0;
		ops++; // set c to 0

		while (c < columns) { // columns = rows, 1 operation + 1 termination
			ops++; // for comparison c < columns

			int next = 0;
			int iNext = 0;
			ops += 2; // assigning next and iNext to 0

			while (iNext < rows) { // 1 operation + 1 termination
				ops++; // for comparison iNext < rows

				// two function calls to rcIndex, where each call costs 1 operation
				// +1 operation for cost of line of code for compound assignment of next
				next += m[rcIndex(r, iNext, columns)] * m[rcIndex(iNext, c, columns)]; // 1 + 1 + 1
				iNext++;
				ops += 4; // compound assignment of next (3 operations) and iNext increment
			}
			ops++; // terminating inner while comparison

			result[rcIndex(r, c, columns)] = next; // cost is 2 (function call + line execution)
			c++;
			ops += 3; // assigning result array (2 operations), increment c
		}
		ops++; // terminating middle while comparison

		r++;
		ops++; // increment r
	}
	ops++; // terminating outer while comparison

	return result; // cost 0
}

// PARAM: arr is array to be sorted, n is siz of array, i should initially = 0
void bsort(int arr[], int n, int i, int &ops) {
	if (i == 0) ops = 0; // only reset count in initial call

	// Bubble down each element
	if ( i < n - 1) {
		ops++; // for i < n - 1 comparison

		// Last i elements are in correct position
		int j = 0;
		ops++; // set j to 0

		while (j < n - i - 1) { // 1 operation + 1 termination
			ops++; // for j < n - i - 1 comparison

			// Compare elements
			if (arr[j] > arr[j + 1]) {
				ops++; // for arr[j] > arr[j = 1] comparison

				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				ops += 3; // assigning temp, arr[j], and arr[j = 1]
			}
			j++;
			ops++; // increment j
		}
		ops++; // terminating while loop

		bsort(arr, n, i + 1, ops); // added ops reference
		ops++; // recursive call bsort()
	}
}

// PRE: n is a power of 2 greater than zero.
// PRE: initial call should be to i = 0
// e.ge pattern(8, 0)
void pattern(int n, int i, int &ops) {
	if (i == 0) ops = 0; // only initialize ops to 0 in initial call

	if (n > 0) {
		ops++; // for comparison n > 0

		pattern(n/2, i, ops); // pass ops by reference, count once
		ops++; // recursive call pattern()

		// Print i spaces
		cout << string(i, ' ');
		ops += 4; // print statement + string() function -> 1 + 3

		// A loop to print n asterisks, each one followed by a space
		int ast = 0;
		ops++;

		while (ast < n) {
			ops++; // for comparison ast < n

			cout << "* ";
			ast++;
			ops += 2; // printing asterisk and increment ast
		}
		ops++; // terminating while loop

		cout << endl;
		i += n;
		pattern(n / 2, i, ops); // pass ops by reference
		ops += 3; // printing newline, compound assign i, recursive call pattern() function
	}
}

// Desc: Prints the first n columns of an n variable truth table
void tt(int n, int &ops) {
	int rows = (int)pow(2, n); // line execution + call pow() function -> 1 + 1 operations
	int columns = n;
	int r = 0;
	ops = 4; // assign rows (2), columns, r

	while (r < rows) {
		ops++; // while loop comparison

		int c = 0;
		ops++; // set c to 0

		while ( c < columns) {
			ops++; // while loop comparison

			if ((r / (int)pow(2, n - c - 1)) < 1) { // if statement + pow() function -> 1 + 1 operations
				cout << "T ";
				ops += 3; // if comparison with pow() function, and printing T
			}
			else {
				cout << "F ";
				ops += 3; // printing F, still counts if statement (2)
			}
			c++;
			ops++; // incrementing c
		}
		ops++; // terminating inner while loop

		r++;
		cout << endl;
		ops += 2; 	
	}
	ops++; // terminating outer while loop
}
