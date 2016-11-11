#include "ising.h"
#include <mpi.h>

// input arguments: [dim] [temp_init] [temp_final] [temp_step] [cycles]
int main(int argc, char *argv[]) {

    int world_size;
    int world_rank;

    arma::vec expected_values = arma::zeros<arma::mat>(5); //arma::zeros<arma::mat>(5); //= arma::zeros<arma::mat>(5);
    arma::vec tot_expected_values = arma::zeros<arma::mat>(5);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int dim = atoi(argv[1]);
    double temp_init  = atof(argv[2]);
    double temp_final = atof(argv[3]);
    double temp_step  = atof(argv[4]);
    int cycles = atoi(argv[5]);

    // dont need this!
    //arma::vec temp_steps = arma::linspace<arma::vec>(temp_init, temp_final, stuff_to_do);
    //std::cout << temp_steps << std::endl;

    MPI_Bcast(&cycles, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&temp_init, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&temp_final, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double timeStart, timeStop, totalTime;

    timeStart = MPI_Wtime();
    Ising myFriendTheIsingModel = Ising(dim, world_rank, world_size);
    for (float temp=temp_init; temp <= temp_final; temp += temp_step) {
        myFriendTheIsingModel.initialise_system(temp);
        myFriendTheIsingModel.simulate(cycles, expected_values);
    }
    timeStop = MPI_Wtime();

    totalTime = timeStop - timeStart;
    if (world_rank == 0) {
        std::cout << "Time elapsed: " << totalTime << " on " << world_size << " processors." << std::endl;
    }

    MPI_Finalize();
    return 0;
}
