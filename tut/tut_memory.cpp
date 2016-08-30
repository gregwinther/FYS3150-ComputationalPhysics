#include <iostream>
#include <fstream>

using namespace std;

void makeMeYoung(int* age) {

	cout << "I used to be " <<  *age << endl;
	*age = 21;

}

void actYourAge(int& age) {

	age = 39;

}

int main() {
	
	int myAge = 39;
	char myGrade = 'A';

	cout << "Size of int " << sizeof(myAge) << endl;
	cout << "Size of char " << sizeof(myGrade) << endl;

	cout << "myAge is located at " << &myAge << endl;

	cout << "\nMore somewhat important stuff: \n" << endl;

	// Reference and get data :)

	int* agePtr = &myAge;

	cout << "Address of pointer to variable myAge: " << agePtr << endl;

	cout << "You can also get the data from this pointer!" << endl;
	cout << "Data at memory address: " << *agePtr << "\n" << endl;

	// This seems important. Check this out :)

	int badNums[5] = {4, 13, 14, 24, 34};

	int* numArrayPtr = badNums;

	cout << "Address: " << numArrayPtr << " Value: " << *numArrayPtr << endl;

	numArrayPtr++;

	cout << "Address: " << numArrayPtr << " Value: " << *numArrayPtr << endl;

	// Same as above! 
	//When you are passing a pointer you are passing a reference that can be changed
	cout << "Address: " << badNums << " Value: " << *badNums << endl;

	cout << endl;

	// And array name is just a pointer to the array

	// Passing by reference
	makeMeYoung(&myAge);

	cout << "I'm " << myAge << " years old now.\n" << endl;

	// Difference between a reference and a pointer?
	
	int& ageRef = myAge;
	
	cout << "myAge: " << myAge << endl;

	ageRef++;

	cout << "myAge: " << myAge << endl;

	actYourAge(ageRef);

	cout << "myAge: " << myAge << endl;

	cout << "It did indeed change! \n" << endl;

	/*	When to use pointers and when to use references?
		Use pointers when: If you don't want to have to initialize 
		at declaration. Possible to assing another variable.
		if you don't need to change whatever you are pointing at
		use a reference. */

	return 0;
}