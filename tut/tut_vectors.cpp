#include <iostream>
#include <vector>

using namespace std;

int main() {

	// initial size is ten of this vector
	vector <int> lotteryNumVect(10);

	int lotteryNumArray[5] = {4, 13, 14, 24, 34};

	// Inserting at beginning of vector from array, first three
	lotteryNumVect.insert(lotteryNumVect.begin(), lotteryNumArray, 
		lotteryNumArray+3);

	//cout << lotteryNumVect << endl; !! Does not work..

	cout << lotteryNumVect.at(2) << endl;

	// insert at index 5
	lotteryNumVect.insert(lotteryNumVect.begin()+5, 44);

	cout << lotteryNumVect.at(5) << endl;

	// Push back adds a value at the end of the vector
	lotteryNumVect.push_back(64);

	cout << "Final value from .back(): " << lotteryNumVect.back() << endl;

	// .front() gets first value :)

	// pops last entry
	lotteryNumVect.pop_back();

	return 0;
}