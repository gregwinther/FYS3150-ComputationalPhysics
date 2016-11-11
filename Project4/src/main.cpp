#include "ising.h"
#include <mpi.h>

int main(int argc, char *argv[]) {

    int world_size;
    int world_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int dim = atoi(argv[1]);
    double temp = atof(argv[2]);
    int cycles = atoi(argv[3]);

    //if (world_rank == world_size - 1) { my_temp_end += temperature_step; }

    Ising myClass = Ising(dim);
    myClass.initialise_system(temp);
    myClass.simulate(cycles);
    //myClass.write_to_terminal();

    MPI_Finalize();

    return 0;
}
