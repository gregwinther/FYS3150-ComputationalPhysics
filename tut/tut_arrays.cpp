#include <iostream>

using namespace std;

int main() {

	int myFavNums[5];

	int badNums[5] = {5, 13, 14, 24, 34};

	cout << "Bad number 1: " << badNums[0] << endl;

	// 2D array
	char myName[4][4] = {	{'G', 'r', 'e', 'g'}, 
							{'W', 'i', 'n', 't'}};

	cout << "Ugly print: " << myName << endl;
	cout << "2nd letter in 2nd array: " << myName[1][1] << endl;

	// change value of array
	myName[0][2] = 'e';

	cout << "New value: " <<myName[0][2] << endl;

	// for loops
	for (int i = 1; i <= 8; i++) {

		cout << i << endl;
	}

	cout << "Nice print: " << endl;
	for (int j = 0; j < 2; j++) {

		for (int k = 0; k < 4; k++) {

			cout << myName[j][k];
		}
		cout << endl;
	}

	// random numbers and while loops (not really random)

	int randNum = (rand() % 100) + 1;

	while (randNum != 100) {

		cout << randNum << ", ";

		randNum = (rand() % 100) + 1;
	
	}

	// Possible to simulate a for loop with a while loop
	// do-while: stuff will get executed at least once..

	cout << endl;

	return 0;
}