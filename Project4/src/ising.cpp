#include "ising.h"
#include <iomanip>
#include <iostream>
#include <time.h>
#include <mpi.h>


Ising::Ising(int lattice_dimension, int rank) {

    this->lattice_dimension = lattice_dimension;
    this->no_of_spins = lattice_dimension*lattice_dimension;
    this->expectations_filename = "expectations.dat";
    this->rank = rank;

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

void Ising::simulate(int cycles, arma::vec &expected_values) {

    //this->expected_values = expected_values;

    for (int i = 0; i < cycles; ++i) {

        metropolis();

        expected_values(0) += energy;
        expected_values(1) += energy*energy;
        expected_values(2) += magnetisation;
        expected_values(3) += magnetisation*magnetisation;
        expected_values(4) += fabs(magnetisation);

        if ((i > 0) && (i % 100))  output(i, expected_values);
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
/*
void Ising::write_to_terminal() {
  using namespace std;
    cout << setw(25) << "Temperature: " << setw(10) << setprecision(8) << temperature << endl;
    cout << setw(25) << "Expected energy: " << setw(10) << setprecision(8) << expected_energy << endl;
    cout << setw(25) << "Specific heat: " << setw(10) << setprecision(8) << specific_heat << endl;
    cout << setw(25) << "Susceptibility: " << setw(10) << setprecision(8) << susceptibility << endl;
    cout << setw(25) << "Expected abs. magnetis.: " << setw(10) << setprecision(8) << exp_abs_magnetisation << endl;
    //cout << setw(20) << setprecision(8) << number_of_accepted_states / (double) cycles << endl;
}*/

void Ising::output(int current_cycle, arma::vec &expected_values) {

    arma::vec tot_expected_values = arma::zeros<arma::mat>(5);

    // Divide by total number of cycles in order to get expected values
    double normalising_coeff = 1.0 / ((double) current_cycle);

    // Reducing threads to one
    MPI_Reduce(&expected_values(0), &tot_expected_values(0), 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&expected_values(1), &tot_expected_values(1), 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&expected_values(2), &tot_expected_values(2), 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&expected_values(3), &tot_expected_values(3), 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&expected_values(4), &tot_expected_values(4), 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Normalising
    double ev_E = tot_expected_values(0) * normalising_coeff;
    double ev_E2 = tot_expected_values(1) * normalising_coeff;
    double ev_M = tot_expected_values(2) * normalising_coeff;
    double ev_M2 = tot_expected_values(3) * normalising_coeff;
    double ev_Ma = tot_expected_values(4) * normalising_coeff;

    // Variance
    double var_E = (ev_E2 - ev_E*ev_E) / no_of_spins;
    double var_M = (ev_M2 - ev_Ma*ev_Ma) / no_of_spins;

    // The interesting quantities
    expected_energy 		= ev_E / no_of_spins;
    expected_magnetisation 	= ev_M / no_of_spins;
    specific_heat			= var_E / (temperature*temperature);
    susceptibility			= var_M / temperature;
    exp_abs_magnetisation 	= ev_Ma / no_of_spins;

    for( int i = 0; i < 5; i++) {
        MPI_Reduce(&expected_values[i], &tot_expected_values[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    }

    // Writing to file with "master thread"
    using namespace  std;
    if(rank == 0) {
        ofstream ofile;
        ofile.open(expectations_filename, ios::app);
        ofile << setiosflags(ios::showpoint | ios::uppercase);
        ofile << setw(15) << setprecision(8) << temperature;
        ofile << setw(15) << setprecision(8) << expected_energy;
        ofile << setw(15) << setprecision(8) << specific_heat;
        ofile << setw(15) << setprecision(8) << expected_magnetisation;
        ofile << setw(15) << setprecision(8) << susceptibility;
        ofile << setw(15) << setprecision(8) << exp_abs_magnetisation << endl;
        ofile.close();
    }
}
