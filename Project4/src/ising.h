#pragma once
#include <armadillo>

class Ising {
    private:

        int lattice_dimension;
        int no_of_spins;
        int no_of_accepted_states;

        int rank = 0;

		arma::mat lattice;

        arma::vec delta_energy = arma::zeros<arma::mat>(17);
        //arma::vec* expected_values;// = arma::zeros<arma::mat>(5);
        std::string expectations_filename;

		double temperature;

        double expected_energy;
		double expected_magnetisation;
		double specific_heat;
        double susceptibility;
        double exp_abs_magnetisation;

		double energy;
        double magnetisation;

        void metropolis();

		int periodic_boundary_translation(int x, int dimension, int translation);
        double get_energy_of_site(int x, int y);
        void output(int current_cycle, arma::vec &expected_values);

    public:

        Ising(int lattice_dimension, int rank);
		
		void initialise_system(double temp);
        void simulate(int cycles, arma::vec &expected_values);
        void write_to_terminal();

};
