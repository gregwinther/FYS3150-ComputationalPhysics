#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	string numberGuessed;
	int intNumberGuessed;

	do {
		
		cout << "Guess number between 1 and 10: ";

		getline(cin, numberGuessed);

		intNumberGuessed = stoi(numberGuessed);

		cout << intNumberGuessed << endl;


	} while(intNumberGuessed != 4);

	cout << "You win" << endl;


	return 0;

}