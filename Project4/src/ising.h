#include <string>

class Ising {
    private:

        int lattice_dimension;
        int no_of_spins;
        int no_of_accepted_states;

        int rank;
        int world_size;

        double** lattice;

        double delta_energy [17];
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
        void output(int current_cycle, double (&expected_values)[5]);

    public:

        Ising(int lattice_dimension, int rank, int world_size);
		
		void initialise_system(double temp);
        void simulate(int cycles, double (&expected_values)[5]);
        void write_to_terminal();

};
