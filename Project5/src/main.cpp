#include <iostream>
#include <ctime>
#include <string.h>
#include "functions.h"



int main() {

    std::string filename     = "data.dat";   // Output filename

    double m0           =  100;         // Initial wealth
    int N               = 1000;         // No. of agents
    int transactions    =  1e7;         // No. of transactions
    int simulations     =  1e3;         // No. of simulations
    double lambda       =  0.5;         // Propensity to save
    double alpha        =  2.0;         // Wealth proximity variable
    double gamma        =  0.0;         // Past interaction variable

    arma::vec agents(N);    // Agent vector
    arma::vec totagents(N); // Sum of agents over all simulations

    // Seeding RNG
    srand(time(NULL));

    // Timer variables
    clock_t start, end;
    // Start timer
    start = clock();

    // Start simulations
    for (int i = 0; i < simulations; i++) {

        // Print progress
        std::cout << "Simulation no. " << i << std::endl;

        // Assign intitial wealth to all agents
        agents.fill(m0);

        // Trade!
        trade(N, transactions, agents, lambda, alpha, gamma);

        // Sort and add equilibrium wealth to total
        totagents += arma::sort(agents);
    }

    // Mean value of all simulations
    agents = totagents/simulations;

    // Write data to file
    output(N, agents, filename);

    // Stop timer
    end = clock();

    std::cout << "Time elapsed: " << (double) (end - start) / CLOCKS_PER_SEC << " seconds." << std::endl;

}
