#include <iostream>
#include <math.h>
#include <armadillo>

using namespace std;

int main(int argc, char *argv[])
{

    arma::mat A(5,5, arma::fill::randu);

    cout << A << endl;

}
