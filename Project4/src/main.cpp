#include "ising.h"

int main(int argc, char *argv[]) {
	Ising myClass;
	myClass = Ising::Ising();
	myClass->print_some_number();
	return 0;
}