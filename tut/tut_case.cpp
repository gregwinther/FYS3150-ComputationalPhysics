#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main(){

	int greetingOption = 2;

	switch(greetingOption) {

		case 1:
			cout << "Bojour!" << endl;
			break;

		case 2:
			cout << "Guten Tag" << endl;
			break;

		case 3:
			cout << "Halloooo?" << endl;
			break;

		default:
			cout << "Hello." << endl;

	}

	return 0;
}