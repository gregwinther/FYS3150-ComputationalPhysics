#include <iostream>
#include "functions.h"
#include <time.h>
#include <string.h>

using namespace std;


int main(int argc, char *argv[]) {

    int N = 1000; // No of agents
    int no_of_transactions = 1e7;
    double initial_wealth = 100;
    double savings_rate = 0.25;
    string filename = "stuff.dat";

    arma::vec agents(N);
    agents.fill(initial_wealth);

    // Timer variables
    clock_t start, end;

    // Start timer
    start = clock();

    transact(agents, no_of_transactions, N, savings_rate);
    write_to_file(agents, N, filename);

    // Stop timer
    end = clock();

    cout << "Time elapsed: " << (double) (end - start) / CLOCKS_PER_SEC
         << " seconds." << endl;

    return 0;
}
