#include <iostream>
#include <math.h>
#include <armadillo>

using namespace std;

double maxOffDiagonals(arma::mat &A, int &k, int &l, int n) {

    double max;

    k = 0;
    l = 0;

    for (int i = 0; i < n; ++i) {

        // Indexing will only include upper triangular part
        // This assumes that matrix is symmetric
        // Advantage: excludes diagonal, which is what we want
        for (int j = i+1; j < n; ++j) {

            double aij = fabs(A(i,j));

            if (aij > max) {
                // Maximum non-diagonal value
                max = aij;
                // Position of this value
                k = i;
                l = j;
            }
        }
        cout << "Largest off-diagonal element is: " << maxOffDiagonals(A, k, l, n) << endl;

    }

    return max;
}

void jacobiRotation(arma::mat &A, arma::mat &R, int &k, int &l, int n) {
    // A is the input matrix and S is the matrix with eigenvectors after
    // enough rotations

    // Initiating variables
    double tau, t, c, s;

    /* -----------------------------------------------
     * COMPUTING c = cosine(angle) AND s = sine(angle)
     * -----------------------------------------------
     *
     * I don't want to compute cosine or sine of anything.
     * (Important steps to the right)
     * tan(angle) = t = sin / cos = s / c
     * cot(2*angle) = tau = (a_ll - a_kk) / 2*a_kl 	->	(No 1: tau)
     * using: cot(2*angle) = 1/2 * (cot(angle) - tan(angle))
     * -> t**2 + 2*tau*t - 1 = 0
     * which gives t = +/- 1/ (tau + sqrt(1 + tau**2))->(No. 2: t)
     * FINALLY: c = 1 / (sqrt(1 + t**2)) AND s = c*t -> (No.3: c and s)
     */

    // No. 1: tau
    tau = (A(l,l) - A(k,k)) / (2*A(k,l));

    // No. 2: t
    // t can be either + or - depending on t**2 + 2*tau*t
    if (tau >= 0) {
        t = -tau + sqrt(1 + tau*tau); 		// tan(angle)
    } else {
        t = -tau - sqrt(1 + tau*tau);		// tan(angle)
    }

    // No. 3:
    c = 1.0 / (sqrt(1 + t*t));				// cos(angle)
    s = c*t;								// sin(angle)

    /* ----------------------------------------------
     * ROTATING
     * ----------------------------------------------
     * for i neq k, i neq l:
     * 1) b_ii = a_ii
     * 2) b_ik = a_ik*c - a_il*s
     * 3) b_il = a_il*c - a_ik*s
     * for all i:
     * 4) b_kk = a_kk*c*c - 2*a_kl*c*s + a_ll*s*s
     * 5) b_ll = a_ll*c*c + 2*a_kl*c*s + a_kk*s*s
     * 6) b_kl = (a_kk - a_ll)*c*s + a_kl*(c*c - s*s)
     * The last term should be zero by definition of c and s
     * can be hardcoded to zero
     * b_?? are not used, instead a_?? is overwritten
     * this means that 1) is unnecesary
     */

    // Declaring variables
    double a_kk, a_ll, a_il, a_ik;

    a_kk = A(k, k);
    a_ll = A(l, l);
    A(k ,k) = a_kk*c*c - 2*A(k, l)*c*s + a_ll*s*s; // 4)
    A(l, l) = a_ll*c*c + 2*A(k, l)*c*s + a_kk*s*s; // 5)
    A(l, k) = 0.0; // Hard-coding non-diagonal elements,
    A(k, l) = 0.0; // these should be equal to zero

    for (int i = 0; i < n; i++) {
        // i neq k, i neq l
        if (i != k && i != l) {
            a_ik = A(i, k);
            a_il = A(i, l);
            A(i, k) = a_ik*c - a_il*s; // 2)
            A(k, i) = A(i, k); // Symmetric matrix
            A(i, l) = a_il*c - a_ik*s; // 3)
            A(l, i) = A(l, i);
        }

    // The new eigenvectors
    double r_ik = R(i, k);
    double r_il = R(i, l);
    R(i, k) = c*r_ik - s*r_il;
    R(i, l) = c*r_il + s*r_ik;

    }


}


void jacobiMethod(arma::mat &A, arma::mat &R, int &k, int &l, int n) {

    // Tolerance for the non-diagonals
    double eps = 1.0E-8;

    double max_nondiagonal = maxOffDiagonals(A, k, l, n);

    // The Jacobi rotation algorithm
    while (max_nondiagonal > eps) {
        int p, q;
        max_nondiagonal = maxOffDiagonals(A, p, q, n);
        jacobiRotation(A, R, k, l, n);
        cout << R << endl;
    }

}
