#include "a3.h"

int sumSquares(int arr[], int n, int & ops) {
	int i = 0;
	int sum = 0;
	ops = 2;
	while ( i < n) {
		sum += arr[i] * arr[i];
		i++;
		ops += 3;
	}
	ops++;
	return sum;
}

void sumSquareTest()
{
       cout << "SUM OF SQUARES TEST" << endl;
       int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
       int n = 10;
       int cost = 0;
       cout << "sum of squares = " << sumSquares(arr, n, cost);
       cout << endl << "cost = " << cost;
       cout << endl << "t(sumSquares): 3n+3 = " << 3 * n + 3;
       cout << endl << "--------------" << endl << endl;
}

void cartesianProductTest() {
	int cost = 0;
	int arr[] = { 1,2 };
	int n = 2;
	cartesianProduct(arr, n, cost);
	cout << endl << "cost = " << cost << endl;
}

void triangleTest() {
    int cost = 0;
    int x = 3;
    triangle(x, cost);
    cout << endl << "cost = " << cost << endl;
}

void bsortTest() {
    int cost = 0;
    int arr[] = {3, 1, 2};
    int n = 3;
    bsort(arr, n, 0, cost);
    cout << endl << "cost = " << cost << endl;
}

void matrixSelfMultiplyTest() {
    int cost = 0;
    int m[] = {1, 2, 3, 4}; // 2x2 matrix
    int rows = 2;
    int* result = matrixSelfMultiply(m, rows, cost);
    cout << endl << "cost = " << cost << endl;
    delete[] result;
}

void rcIndexTest() {
    int cost = 0;
    int r = 1, c = 2, columns = 3;
    int idx = rcIndex(r, c, columns); // No cost counting needed here
    cout << "rcIndex = " << idx << endl;
}

void patternTest() {
    int cost = 0;
    int n = 8;
    pattern(n, 0, cost);
    cout << endl << "cost = " << cost << endl;
}

void ttTest() {
    int cost = 0;
    int n = 3;
    tt(n, cost);
    cout << endl << "cost = " << cost << endl;
}

int main (void) {
	patternTest();
}
