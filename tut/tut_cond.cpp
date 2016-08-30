#include <iostream>

using namespace std;

int main(){

	// ==, !=, <, >, <=, >=, &&, ||, !

	int age = 70;
	int ageAtLastExam = 16;
	bool isNotIntoxicated = true;

	if ((age >= 1) && (age < 16)) {

		cout << "You cannot drive!" << endl;
	
	} else if(! isNotIntoxicated) {

		cout << "You cannot drive!" << endl;

	} else if ((age >= 80) && ((age > 100) || ((age - ageAtLastExam) > 5))) {

		cout << "You cannot drive!" << endl;

	} else {

		cout << "You can drive." << endl;
	}

	// Conditional variable assignment
	int largestNum = (8>2) ? 8 : 2;
	cout << "The largest numer of 8 and 2 is " << largestNum << endl;

	return 0;
}