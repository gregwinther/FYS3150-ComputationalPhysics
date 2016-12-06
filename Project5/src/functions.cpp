#include "functions.h"
#include <time.h>
#include <iostream> // std::cout, std::endl
#include <armadillo>
#include <string.h>
#include <iomanip>  // std::setiosflags

void transact(int N, int no_of_transactions, arma::vec (&agents), double lambda, double alpha, double gamma) {

    // Matrix registring if a previous transaction has taken place between two agents
    arma::mat C = arma::zeros<arma::mat>(N,N);

    /*
     * The following variables are used to check whether equilibrium is reached
     * The initial values are arbitrarily set in order to break first if-test
     * The variables are reset for every simulation
     */

    double avgVarBlockOld   = 1e100;
    double varVarBlockOld   = 1e100;
    double cumVarBlock      =     0;
    double comVar2Block     =     0;
    int blockSize           =   1e4;

    // Random number generator is seeded by time
    srand(time(NULL));

    for (int i = 0; i < no_of_transactions; i++) {

        // Pick to agents at random
        int agent_i = (int) rand() % N;
        int agent_j = (int) rand() % N;

        // Find the wealth of these agents
        double m_i = agents(agent_i);
        double m_j = agents(agent_j);

        // Now to account for favoured wealth, previous transactions and i =! j

        // Need random number for comparisson
        double random_number = (double) rand() / RAND_MAX;

        // Find number of previous transactions in matrix C
        int previous_transactions = C(agent_i, agent_j);

        /*
         * The logical statement in the following while loops will check if the agents are
         * "good enough": Have they dealed in the past and are close in the "food chain".
         * Furthermore: checks if agents are the same. Until a new good match of agents are
         * found, new random agents are picked.
         */

        while ( (pow(fabs(m_i-m_j),-alpha)*pow(previous_transactions+1, gamma) < random_number)
                || (agent_i==agent_j)) {

            // Pick new agents ...
            int agent_i = (int) rand() % N;
            int agent_j = (int) rand() % N;

            // ... find wealth of these ...
            double m_i = agents(agent_i);
            double m_j = agents(agent_j);

            // ... update previous transactions ...
            int previous_transactions = C(agent_i, agent_j);

            // ... and update the random comparison number

        }

        // If everything is good the algorithm can proceed.

        // Random value of transaction b/w 0 and 1
        double epsilon = (double) rand() / RAND_MAX;

        // Transaction takes place, but some is saved (lambda)
        double delta_m = (1 - lambda) * (epsilon*m_j - (1 - epsilon)*m_i);
        agents(agent_i) += delta_m;
        agents(agent_j) -= delta_m;

        // Register that a transaction has taken place betwwen these two agents
        C(agent_i, agent_j) += 1;
        C(agent_j, agent_i) += 1;


        /*
         * This test breaks the for loop when an equilibrium is reached
         * This is done by studying the variance of the variance for a
         * block of the transactions that take place
         */

        double variance = arma::var(agents);
        cumVarBlock += var;
        cumVar2Block += var*var;

        // Enter here at the correct place: end of block
        if (i % blockSize == 0) {


        }

    }



    /*
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
    */

}

void output(int N, arma::vec agents, std::string filename) {

    using namespace std;
    ofstream ofile;
    ofile.open(filename, ios::out);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    for (int i = 0; i < N; i++) {
        ofile << setw(15) << setprecision(8) << agents(i) << endl;
    }
    ofile.close();

}
