#include <iostream>
#include "functions.h"
# include <time.h>

using namespace std;


int main(int argc, char *argv[]) {

    int N = 10; // No of agents
    int no_of_transactions = 1e7;
    double initial_wealth = 100;

    arma::vec agents(N);
    agents.fill(initial_wealth);

    cout << "No of agents = " << N << ". Sum = " << arma::sum(agents) << endl;
    cout << "Initial wealth distribution: " << endl;
    cout << agents << endl;
    transact(agents, no_of_transactions, N);
    cout << "Wealth distribution after " << no_of_transactions << " transactions"
         << ". Sum = " << arma::sum(agents) << endl;
    cout << agents << endl;

    return 0;
}
