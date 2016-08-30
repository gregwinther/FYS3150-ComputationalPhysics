#include <iostream.h>

using namespace std;

int main() {

	do {
		
		cout << "Guess number between 1 and 10: ";

		getline(cin, numberGuessed);

		intNumberGuessed = stoi(numberGuessed);


	} while(intNumberGuessed != 4);


	return 0;

}