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

    A 	<< 1 << 2 << 3 << arma::endr
        << 2 << 2 << 4 << arma::endr
        << 3 << 4 << 5 << arma::endr;

    cout << A << endl;
    cout << "Largest off-diagonal element is: " << maxOffDiagonals(A, k, l, n) << endl;
    cout << "k is different from zero? " << (k != 0) << endl;

}
