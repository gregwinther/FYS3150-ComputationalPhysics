#include <iostream>
#include <math.h>
#include <armadillo>

#include <jacobimethod.h>

using namespace std;

int main(int argc, char *argv[])
{
    int n = 3;
    int k = 0;
    int l = 0;

    arma::mat A(n,n);
    arma::mat R; R.eye(n,n);

    A 	<< 4 << 1 << 0 << arma::endr
        << 1 << -1 << 0 << arma::endr
        << 0 << 0 << 5 << arma::endr;

    double maxdiag = maxOffDiagonals(A, k, l, n);
    cout << A << endl;
    cout << "k is different from zero? " << (k != 0) << endl;

    jacobiMethod(A, R, k, l, n);


}
