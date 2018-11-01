#include "ising.h"
#include <iomanip>
#include <iostream>
#include <time.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include "lib.h"
#include <mpi.h>

Ising::Ising(int lattice_dimension, int rank, int world_size) {

    this->lattice_dimension = lattice_dimension;
    this->no_of_spins = lattice_dimension*lattice_dimension;
    this->expectations_filename = "expectations.dat";
    this->rank = rank;
    this->world_size = world_size;

    //lattice = arma::mat(lattice_dimension, lattice_dimension);
    this->lattice = (int**) matrix(lattice_dimension, lattice_dimension, sizeof(double));

    double delta_energy[17];

    energy = 0;
    magnetisation = 0;

}

void Ising::initialise_system(double temp) {
    temperature = temp;

    // Reset variables
    energy = 0;
    magnetisation = 0;
    no_of_accepted_states = 0;

    // Possible energies
    for (int i = -8; i <= 8; i++) delta_energy[i + 8] = 0;
    for (int i = -8; i <= 8; i += 4) delta_energy[i + 8] = exp(-i/temperature);

    // Time as seed for random number generator
    srand(time(NULL));

    for (int i = 0; i < lattice_dimension; i++) {
        for (int j = 0; j < lattice_dimension; j++) {

            // Start in random configuration
            lattice[i][j] = ((int(rand() / (RAND_MAX)) > 0.5) ? 1: -1);

            // Magnetisation
            magnetisation += lattice[i][j];

        }
    }

    // Initial energy - Mulitply every sites spin direction with neighbhours
    for (int i = 0; i < lattice_dimension; ++i) {
        for (int j = 0; j < lattice_dimension; ++j) {
            energy -= lattice[i][j]
                    * (lattice[periodic_boundary_translation(i, lattice_dimension, -1)][j]
                    +  lattice[i][periodic_boundary_translation(j, lattice_dimension, -1)]);
        }
    }
}

void Ising::simulate(int cycles, double (&expected_values)[5]) {

    int no_intervals  = cycles / world_size;
    int my_loop_begin = rank * no_intervals + 1;
    int my_loop_end   = (rank + 1) * no_intervals;

    if ( (rank == world_size - 1) && (my_loop_end < cycles)) my_loop_end = cycles;

    for (int i = my_loop_begin; i <= my_loop_end; i++) {

        metropolis();

        if (i > (no_intervals*0.15)) { // Steady state reached after 15 % of cycles
            expected_values[0] += energy;
            expected_values[1] += energy*energy;
            expected_values[2] += magnetisation;
            expected_values[3] += magnetisation*magnetisation;
            expected_values[4] += fabs(magnetisation);
            //output(i, expected_values);
        }
    }

    output(no_intervals, expected_values);

    // Divide by total number of cycles in order to get expected values
    double normalising_coeff = 1.0 / ((double) cycles);
    double ev_E  = expected_values[0] * normalising_coeff;
    double ev_E2 = expected_values[1] * normalising_coeff;
    double ev_M  = expected_values[2] * normalising_coeff;
    double ev_M2 = expected_values[3] * normalising_coeff;
    double ev_Ma = expected_values[4] * normalising_coeff;

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

// Metropolis-Hastings. One single Monte-Carlo step.
void Ising::metropolis() {

    for (int i = 0; i < no_of_spins; i++) {
        int random_x = rand() % lattice_dimension;
        int random_y = rand() % lattice_dimension;

        int delta_E = get_energy_of_site(random_x, random_y);

        if (( double(rand()) * 1. / RAND_MAX) <= delta_energy[delta_E + 8]) {

            lattice[random_x][random_y] = -1 * lattice[random_x][random_y];
            magnetisation += (double) 2 * lattice[random_x][random_y];
            energy += (double) delta_E;
            no_of_accepted_states++;

        }
    }
}

// Calculates
int Ising::get_energy_of_site(int x, int y) {
    int north = lattice[x][periodic_boundary_translation(y, lattice_dimension, -1)];
    int south = lattice[x][periodic_boundary_translation(y, lattice_dimension, 1)];
    int east  = lattice[periodic_boundary_translation(x, lattice_dimension, +1)][y];
    int west  = lattice[periodic_boundary_translation(x, lattice_dimension, -1)][y];
    int self  = lattice[x][y];
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
    cout << setw(25) << "Expected magnetisation: " << setw(10) << setprecision(8) << expected_magnetisation << endl;
    //cout << setw(20) << setprecision(8) << number_of_accepted_states / (double) cycles << endl;
}


void Ising::output(int current_cycle, double (&expected_values)[5]) {

    // Divide by total number of cycles in order to get expected values
    // Divde by number of threads to avereage out MPI_SUM operator
    double normalising_coeff = 1.0 / ((double) current_cycle) / world_size;

    // Array to reduce threads to
    double tot_expected_values[5];
    for (int i = 0; i < 5; i++) tot_expected_values[i] = 0;

    // Reducing threads to one
    MPI_Reduce(&expected_values[0], &tot_expected_values[0], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&expected_values[1], &tot_expected_values[1], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&expected_values[2], &tot_expected_values[2], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&expected_values[3], &tot_expected_values[3], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&expected_values[4], &tot_expected_values[4], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Normalising
    double ev_E  = tot_expected_values[0] * normalising_coeff;
    double ev_E2 = tot_expected_values[1] * normalising_coeff;
    double ev_M  = tot_expected_values[2] * normalising_coeff;
    double ev_M2 = tot_expected_values[3] * normalising_coeff;
    double ev_Ma = tot_expected_values[4] * normalising_coeff;

    // Variance
    double var_E = (ev_E2 - ev_E*ev_E) / no_of_spins;
    double var_M = (ev_M2 - ev_Ma*ev_Ma) / no_of_spins;

    // The interesting quantities
    expected_energy 		= ev_E / no_of_spins;
    expected_magnetisation 	= ev_M / no_of_spins;
    specific_heat			= var_E / (temperature*temperature);
    susceptibility			= var_M / temperature;
    exp_abs_magnetisation 	= ev_Ma / no_of_spins;

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
        ofile << setw(15) << setprecision(8) << exp_abs_magnetisation;
        ofile << setw(15) << setprecision(8) << no_of_accepted_states << endl;
        ofile.close();
    }
}
