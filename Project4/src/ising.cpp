#include "ising.h"
#include <iomanip>
#include <iostream>
#include <time.h>

Ising::Ising(int lattice_dimension) {

    this->lattice_dimension = lattice_dimension;
    this->no_of_spins = lattice_dimension*lattice_dimension;

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

		}
	}

    // Initial energy - Mulitply every sites spin direction with neighbhours
	for (int i = 0; i < lattice_dimension; ++i) {
		for (int j = 0; j < lattice_dimension; ++j) {
			energy -= lattice(i, j) 
					* (lattice(periodic_boundary_translation(i, lattice_dimension, -1), j)
					+  lattice(i, periodic_boundary_translation(j, lattice_dimension, -1)));
		}
	}	
}

void Ising::simulate(int cycles) {

    for (int i = 0; i < cycles; ++i) {

        metropolis();

        expected_values(0) += energy;
        expected_values(1) += energy*energy;
        expected_values(2) += magnetisation;
        expected_values(3) += magnetisation*magnetisation;
        expected_values(4) += fabs(magnetisation);
    }

    // Divide by total number of cycles in order to get expected values
    double normalising_coeff = 1.0 / ((double) cycles);
    double ev_E  = expected_values(0) * normalising_coeff;
    double ev_E2 = expected_values(1) * normalising_coeff;
    double ev_M  = expected_values(2) * normalising_coeff;
    double ev_M2 = expected_values(3) * normalising_coeff;
    double ev_Ma = expected_values(4) * normalising_coeff;

    // Variance
    double var_E = (ev_E2 - ev_E*ev_E) / no_of_spins;
    double var_M = (ev_M2 - ev_Ma*ev_Ma) / no_of_spins;

    // The interesting quantities
    expected_energy 		= ev_E / no_of_spins;
    expected_magnetisation 	= ev_M / no_of_spins;
    specific_heat			= var_E / (temperature*temperature);
    susceptibility			= var_M / temperature;
    exp_abs_magnetisation 	= ev_Ma / no_of_spins;

}

// One step of Metropolis-Hastings. One single Monte-Carlo cycle
void Ising::metropolis() {
    for (int i = 0; i < no_of_spins; i++) {
        int random_x = rand() % lattice_dimension;
        int random_y = rand() % lattice_dimension;

        int delta_E = get_energy_of_site(random_x, random_y);

        if (( (double) rand() * 1. / RAND_MAX) <= delta_energy(delta_E + 8)) {

            lattice(random_x, random_y) = -1 * lattice(random_x, random_y);
            magnetisation += (double) 2 * lattice(random_x, random_y);
            energy += (double) delta_E;
            no_of_accepted_states++;

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

void Ising::write_to_terminal() {
  using namespace std;
    cout << setw(25) << "Temperature: " << setw(10) << setprecision(8) << temperature << endl;
    cout << setw(25) << "Expected energy: " << setw(10) << setprecision(8) << expected_energy << endl;
    cout << setw(25) << "Specific heat: " << setw(10) << setprecision(8) << specific_heat << endl;
    cout << setw(25) << "Susceptibility: " << setw(10) << setprecision(8) << susceptibility << endl;
    cout << setw(25) << "Expected abs. magnetis.: " << setw(10) << setprecision(8) << exp_abs_magnetisation << endl;
    //cout << setw(20) << setprecision(8) << number_of_accepted_states / (double) cycles << endl;
}
