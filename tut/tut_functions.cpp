#include <iostream>

using namespace std;

// Adding function. secondNum has a default
int addNumbers(int firstNum, int secondNum = 0) {

	int combinedValue = firstNum + secondNum;

	return combinedValue;

}

// Overload function
int addNumbers(int firstNum, int secondNum, int thirdNum) {

	return firstNum + secondNum + thirdNum;

}

// recursive function, factorial
int getFactorial(int number) {

	int sum;
	if (number == 1) sum = 1;
	else sum = getFactorial(number - 1) * number;
	return sum;


}

int main() {

	cout << "1 + 0 = " << addNumbers(1) << endl;

	cout << "1 + 5 + 6 = " << addNumbers(1, 5, 6) << endl;

	cout << "Factorial of 6 is " << getFactorial(6) << endl;

	return 0;
}