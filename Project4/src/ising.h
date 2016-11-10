#pragma once

#include <armadillo>

class Ising {
	private:
		int lattice_dimension;

		arma::mat lattice;

		double temperature;

		double expected_energy;
		double expected_magnetisation;
		double specific_heat;
		double susceptibility;

		double energy;
		double magnetisation;

		int periodic_boundary_translation(int x, int dimension, int translation);

	public:
		Ising(int lattice_dimension);
		
		void initialise_system(double temp);
        void simulate(int cycles);

        void metropolis_test();
};
