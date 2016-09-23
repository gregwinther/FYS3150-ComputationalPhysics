#include <iostream>
#include <math.h>
#include <armadillo>

using namespace std;

double offDiagonals(arma::mat A, int n) {

    double max;

    for (int i = 0; i < n; ++i) {

        // Indexing will only include upper triangular part
        // This assumes that matrix is symmetric
        // Advantage: excludes diagonal, which is what we want
        for (int j = i+1; j < n; ++ j) {

            double aij = fabs(A(i,j));

            if (aij > max) {
                max = aij;
            }
        }
    }

    return max;
}

void jacobiRotation(mat A, mat S) {
    // A is the input matrix and S is the Givens rotation matrix



}

void jacobiMethod() {

    // Tolerance for the non-diagonals
    double eps = 1.0E-8;

    double max_nondiagonal;

    // The Jacobi rotation algorithm
    while (max_nondiagonal > eps) {
        int p, q;

    }
}
