#include "ising.h"

int main(int argc, char *argv[]) {
	
    int dim = atoi(argv[1]);
    int temp = atoi(argv[2]);
    int cycles = atoi(argv[3]);
    Ising myClass = Ising(dim);
    myClass.initialise_system(temp);
    myClass.simulate(cycles);
    myClass.write_to_terminal();

    return 0;
}
