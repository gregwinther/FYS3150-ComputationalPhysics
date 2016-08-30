#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {

	// The C way of strings
	char happyArray[6] = {'H', 'a', 'p', 'p', 'y', '\0'};

	string birthdayString = " Birthday";

	cout << happyArray + birthdayString << endl;

	string yourName;
	cout << "What is your name?\n";
	getline(cin, yourName);
	cout << "Hello " << yourName << endl;

	double eulersConstant = 0.57721;
	string eulersGuess;
	double eulersGuessDouble;

	cout << "What is Euler's constant?\n";
	getline(cin, eulersGuess);

	eulersGuessDouble = stod(eulersGuess);

	if (eulersGuessDouble == eulersConstant) {
		cout << "You are right" << endl;
	} else {
		cout << "You are wrong" << endl;
	}

	// Size of string
	cout << "Size of string: " << eulersGuess.size() << endl;
	cout << "Is string empty?: " << eulersGuess.empty( ) << endl;
	cout << eulersGuess.append(" was your guess") << endl;

	// Comparing strings equal: 0, less: 1, greater: -1

	string dogString = "dog";
	string catString = "cat";

	cout << dogString.compare(catString) << endl;
	cout << dogString.compare(dogString) << endl;
	cout << catString.compare(dogString) << endl;

	// .assign() can copy content, or part of content to new string
	// .find() lets you search a string. returns index int
	// .insert() lets you insert at chosen index
	// .erase() is self-explanatory
	// so is .replace()


	return 0;
}