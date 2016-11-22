#include "functions.h"
#include <time.h>
#include <iostream>
#include <armadillo>
#include <string.h>
#include <iomanip>

void transact(arma::vec (&agents), int no_of_transactions, int no_of_agents, double savings_rate) {

    double lambda = savings_rate;

    for (int i = 0; i < no_of_transactions; i++) {

        // Picking random dudes
        int agent1_rank = (int) rand() % no_of_agents;
        int agent2_rank = (int) rand() % no_of_agents;
        // They should not be the same dude
        while (agent1_rank == agent2_rank) agent2_rank = (int) rand() % no_of_agents;

        double epsilon = (double) rand() / RAND_MAX;
        double new_agent1 = lambda * agents(agent1_rank)
                + epsilon * (1 - lambda) * (agents(agent1_rank) + agents(agent2_rank));
        double new_agent2 = lambda * agents(agent1_rank) +
                (1 - epsilon) * (1 - lambda) * (agents(agent1_rank) + agents(agent2_rank));
        agents(agent1_rank) = new_agent1;
        agents(agent2_rank) = new_agent2;
    }

    // Re-seeding random number generator
    srand(time(NULL));
}

void write_to_file(arma::vec data, int vector_length, std::string filename) {

    using namespace std;

    ofstream ofile;
    ofile.open(filename, ios::app);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    for (int i = 0; i < vector_length; i++) {

        ofile << setw(15) << setprecision(8) << data[i] << endl;
    }
    ofile.close();

}
