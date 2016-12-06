#include "functions.h"
#include <time.h>
#include <iostream> // std::cout, std::endl
#include <armadillo>
#include <string.h>
#include <math.h>
#include <iomanip>  // std::setiosflags

void trade(int N, int no_of_transactions, arma::vec (&agents), double lambda, double alpha, double gamma) {

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
    double cumVar2Block     =     0;
    int blockSize           =   1e4;

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

        while ((pow(fabs(m_i - m_j), -alpha)*pow(previous_transactions+1, gamma) < random_number)
               || (agent_i == agent_j)) {

            // Pick new agents ...
            agent_i = (int) rand() % N;
            //agent_j = (int) rand() % N;

            // ... find wealth of these ...
            m_i = agents(agent_i);
            m_j = agents(agent_j);

            // ... update previous transactions ...
            previous_transactions = C(agent_i, agent_j);

            // ... and update the random comparison number
            random_number = (double) rand() / RAND_MAX;

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

        double var = arma::var(agents);
        cumVarBlock += var;
        cumVar2Block += var*var;

        // Enter here at the correct place: end of block
        if (i % blockSize == 0) {

            // Variance of a block "averaged" over the block
            double avgVar  =  cumVarBlock / blockSize;
            double avgVar2 = cumVar2Block / blockSize;

            // Variance of a block of variance
            double varVarBlock = avgVar2 - avgVar*avgVar;

            // Check if variance is low enough
            if ((fabs(avgVarBlockOld - avgVar) / fabs(avgVarBlockOld)     < 0.2) &&
                (fabs(varVarBlock - varVarBlockOld) / fabs(varVarBlockOld) < 0.5)) {

                // Telling a user that an equilibrium has been reached
                std::cout << "Equilibrium reached at transaction no. " << i << std::endl;

                // Done! For now.
                break;

            } else {

                avgVarBlockOld = avgVar;
                varVarBlockOld = varVarBlock;

            }

            // Reset cumulative variance
            cumVarBlock  = 0;
            cumVar2Block = 0;

        }
    }
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
