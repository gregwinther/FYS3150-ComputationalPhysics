#pragma once
#include <armadillo>

class Ising {
	private:
		int lattice_dimension;

		arma::mat lattice;

        arma::vec delta_energy = arma::zeros<arma::mat>(17);

		double temperature;

		double expected_energy;
		double expected_magnetisation;
		double specific_heat;
		double susceptibility;

		double energy;
		double magnetisation;

		int periodic_boundary_translation(int x, int dimension, int translation);
        double get_energy_of_site(int x, int y);

	public:
		Ising(int lattice_dimension);
		
		void initialise_system(double temp);
        void simulate(int cycles);

        void metropolis_test();
};
