#include "ising.h"
#include <mpi.h>

int main(int argc, char *argv[]) {

    int world_size;
    int world_rank;

    arma::vec expected_values = arma::zeros<arma::mat>(5); //arma::zeros<arma::mat>(5); //= arma::zeros<arma::mat>(5);
    arma::vec tot_expected_values = arma::zeros<arma::mat>(5);
    //expected_values* = arma::zeros<arma::mat>(5);
    //expected_values.zeros();

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int dim = atoi(argv[1]);
    double temp = atof(argv[2]);
    int cycles = atoi(argv[3]);

    MPI_Bcast(&cycles, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //if (world_rank == world_size - 1) { my_temp_end += temperature_step; }

    Ising myClass = Ising(dim, world_rank);
    myClass.initialise_system(temp);
    myClass.simulate(cycles, expected_values);
    //myClass.write_to_terminal();



    MPI_Finalize();

    return 0;
}
