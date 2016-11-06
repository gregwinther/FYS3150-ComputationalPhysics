#include "ising.h"
#include <iomanip>
#include <iostream>
#include <time.h>

Ising::Ising(int lattice_dimension) {
	this->lattice_dimension = lattice_dimension;

	lattice = arma::mat(lattice_dimension, lattice_dimension);


	energy = 0;
	magnetisation = 0;
	
}

void Ising::initialise_system(double temp) {
	temperature = temp;

	// reset variables
	energy = 0;
	magnetisation = 0;

	// Time as seed for random number generator
	srand(time(NULL));

	for (int i = 0; i < lattice_dimension; i++) {
		for (int j = 0; j < lattice_dimension; j++) {

			// Start in random configuration
			lattice(i, j) = (((double) rand() / (RAND_MAX)) > 0.5) ? 1: -1;

			magnetisation += lattice(i,j);

			std::cout << lattice(i, j) << std::endl;

		}
	}

	std::cout << "Magnetisation = " << magnetisation << std::endl;

	// Initial energy - Mulitply every sites spin direction with neighbhours
	for (int i = 0; i < lattice_dimension; ++i) {
		for (int j = 0; j < lattice_dimension; ++j) {
			energy -= lattice(i, j) 
					* (lattice(periodic_boundary_translation(i, lattice_dimension, -1), j)
					+  lattice(i, periodic_boundary_translation(j, lattice_dimension, -1)));
		}
	}

	std::cout << "Energy = " << energy << std::endl;

}

// Periodic boundary conditions: "wraps around"
int Ising::periodic_boundary_translation(int x, int dimension, int translation) {
	return (x + dimension + translation) % dimension;
}