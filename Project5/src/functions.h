#include <armadillo>


void transact(arma::vec &agents, int no_of_transactions, int no_of_agents, double savings_rate);

void output(int N, arma::vec agents, std::string filename);
