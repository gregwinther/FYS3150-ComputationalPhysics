#include "functions.h"
#include <time.h>
#include <iostream>
#include <armadillo>

void transact(arma::vec (&agents), int no_of_transactions, int no_of_agents) {

    for (int i = 0; i < no_of_transactions; i++) {
        // Picking random dudes
        int agent1_rank = (int) rand() % no_of_agents;
        int agent2_rank = (int) rand() % no_of_agents;
        // They should not be the same dude
        while (agent1_rank == agent2_rank) agent2_rank = (int) rand() % no_of_agents;
        double epsilon = (double) rand() / RAND_MAX;
        double new_agent1 = epsilon * (agents(agent1_rank) + agents(agent2_rank));
        double new_agent2 = (1 - epsilon) * (agents(agent1_rank) + agents(agent2_rank));
        agents(agent1_rank) = new_agent1;
        agents(agent2_rank) = new_agent2;
    }

    // Re-seeding random number generator
    srand(time(NULL));
}
