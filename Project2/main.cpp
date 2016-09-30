#include <iostream>
#include <math.h>
#include <armadillo>

#include <jacobimethod.h>

using namespace std;

int main(int argc, char *argv[])
{
    int n = 300;

    arma::mat A(n,n);
    arma::mat R; R.eye(n,n);

    //jacobiMethod(A, R, n);

    //A simple 5x5 test matrix
    A << 4 << 1 << 1 << 0 <<-1 << arma::endr
      << 1 << 4 << 0 << 1 <<-1 << arma::endr
      << 1 << 0 << 3 << 0 << 0 << arma::endr
      << 0 << 1 << 0 << 3 << 0 << arma::endr
      <<-1 <<-1 << 0 << 0 << 3 << arma::endr;
      tests(A,R,n);
}
