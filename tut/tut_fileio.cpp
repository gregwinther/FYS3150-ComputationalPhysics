#include <fstream>
#include <iostream>

using namespace std;

int main() {

	string steveQuote = "A day without sunshine is like, you know, night";

	// creat a file
	ofstream writer("stevequote.txt");

	if (! writer) {

		cout << "Error opening file" << endl;
		return -1;

	} else {

		writer << steveQuote << endl;

		writer.close();

	}

	// We want to append now
	ofstream writer2("stevequote.txt", ios::app);

	/* there are several things to do:
		ios::binary : treat file as binary
		ios::in : open a file to read input
		ios::trunc : Default
		ios::out : ope a file to write output
	*/

	if (! writer2) {

		cout << "Error opening file" << endl;
		return -1;


	} else {
	
		writer2 << "\n -Steve Martin" << endl;

		writer2.close();
	
	}

	char letter;

	ifstream reader("stevequote.txt");

	if (! reader) {

		cout << "Error opening file" << endl;
		return -1;

	} else {

		for(int i = 0; ! reader.eof(); i++) {

			reader.get(letter);
			cout << letter;

		}

		cout << endl;
		reader.close();

	}

	return 0;
}