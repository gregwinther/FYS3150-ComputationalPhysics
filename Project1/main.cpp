#include <iostream>

using namespace std;

/*
double forwardsub(double a, int N) {

}
*/

/*
double backwardsub(double *a, double *b, double *c, int n) {

    double* b_tilde = new double[n+1];

    b_tilde[1] = b[1];

    for (int i = 2; i < n+1; i++) {
        b_tilde[i] = b[i] - ((a[i] * c[i-1]))/(b_tilde[i-1]);
        cout << "Item " << i << ": " << b_tilde[i] << endl;
    }

    return *b_tilde;
}
*/


int main(/*int argc, char *argv[]*/)
{
    int n;

    //n = atoi(argv[1]); // Parsing terminal argument dimension
    n = 10;

    // Tridiagonal vectors
    // An extra zero element to simplify indexing
    double* a = new double[n+1];
    double* b = new double[n+1];
    double* c = new double[n+1];

    // Fill vectors
    for (int i = 1; i < n+1; i++) {
        b[i] = 2;
        a[i] = -1;
        c[i] = -1;
    }

    // Zeros at the ends
    c[n] = 0;
    a[1] = 0;

    // Test printy stuff.
    for (int i = 1; i < n+1; i++) {
        cout << a[i] << " " << b[i] << " " << c[i] << endl;
    }

    // construction b_tilde
    double* b_tilde = new double[n+1];
    //*b_tilde = backwardsub(a, b, c, n);

    // computing and printing b_tilde
    b_tilde[1] = b[1];
    cout << b_tilde[1] << endl;

    for (int i = 2; i < n+1; i++) {
        b_tilde[i] = b[i] - ((a[i] * c[i-1]))/(b_tilde[i-1]);
        cout << b_tilde[i] << endl;
    }

    return 0;
}
