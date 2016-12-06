#include <armadillo>


void trade(int N, int no_of_transactions, arma::vec (&agents), double lambda, double alpha, double gamma);

void output(int N, arma::vec agents, std::string filename);
