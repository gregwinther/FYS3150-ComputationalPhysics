// This is a comment
/*
multi-line
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std; // now it is not necessary to include std everywhere

int main() {
	
	cout << "Hello World!" << endl;

	// Variables and data types
	const double PI = 3.145926535;

	char myGrade = 'A';

	bool isHappy = true;

	int myAge = 27;

	float favNum = 7;

	double otherFavNum = 42;

	cout << "Favourite number: " << favNum << endl;

	// number of bytes of datatype
	cout << "Size of int: " << sizeof(myAge) << " bytes" << endl;

	int largestInt = 2147483647;
	int tooLargeInt = 2147483648;

	cout << "largestInt: " << largestInt << endl;
	cout << "tooLargeInt: " << tooLargeInt << endl;

	// incrementation and decrementation

	int five = 5;

	cout << "5++ = " << five++ << endl;
	cout << "++5 = " << ++five << endl;
	cout << "5-- = " << five-- << endl;
	cout << "--5 = " << --five << endl;

	five += 5; five = five + 5; // equvivalent

	// Order of operation: * and / before - and +
	cout << "1 + 2 - 3 * 2 = " << 1 + 2 - 3 * 2 << endl;
	cout << "(1 + 2 - 3) * 2 = " << (1 + 2 - 3) * 2 << endl;

	// Casting
	cout << "4 / 5 = " << 4 / 5 << " <= w/o casting" << endl;
	cout << "4 / 5 = " << (float) 4 / 5 << " <= w/  casting" << endl;

	return 0;

}