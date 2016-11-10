#include "ising.h"
#include <iomanip>
#include <iostream>
#include <time.h>

Ising::Ising(int lattice_dimension) {
    this->lattice_dimension = lattice_dimension;

	lattice = arma::mat(lattice_dimension, lattice_dimension);

    delta_energy = arma::vec(17);

	energy = 0;
	magnetisation = 0;
	
}

void Ising::initialise_system(double temp) {
	temperature = temp;

    // Reset variables
	energy = 0;
    magnetisation = 0;

    // Possible energies
    for (int i = -8; i <= 8; i += 4) delta_energy(i + 8) = exp(-i/temperature);

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

// One step of Metropolis-Hastings. One single Monte-Carlo cycle
void Ising::metropolis_test() {
    for (int i = 0; i < lattice_dimension; i++) {
        int random_x = rand() % lattice_dimension;
        int random_y = rand() % lattice_dimension;

        int delta_E = get_energy_of_site(random_x, random_y);

        if (( (double) rand() * 1. / RAND_MAX) <= delta_energy(delta_E + 8)) {

            lattice(random_x, random_y) = -1 * lattice(random_x, random_y);
            magnetisation += (double) 2 * lattice(random_x, random_y);
            energy += (double) delta_E;

        }
    }
}

// Calculates
double Ising::get_energy_of_site(int x, int y) {
    int north = lattice(x, periodic_boundary_translation(y, lattice_dimension, -1));
    int south = lattice(x, periodic_boundary_translation(y, lattice_dimension, 1));
    int east  = lattice(periodic_boundary_translation(x, lattice_dimension, +1), y);
    int west  = lattice(periodic_boundary_translation(x, lattice_dimension, -1), y);
    int self  = lattice(x, y);
    return 2 * self * (north + south + east + west);
}

// Periodic boundary conditions: "wraps around"
int Ising::periodic_boundary_translation(int x, int dimension, int translation) {
	return (x + dimension + translation) % dimension;
}
