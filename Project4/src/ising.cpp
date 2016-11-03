#include "ising.h"
#include <iomanip>
#include <iostream>

Ising::Ising() {
	this->some_number = 2;
	
}

void Ising::print_some_number() {
	cout << this->some_number << endl;
}