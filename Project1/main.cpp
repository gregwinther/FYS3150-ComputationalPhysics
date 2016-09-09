#include <iostream>
#include <cmath>

using namespace std;

double RHS(double x) {
    return 100*exp(-10*x);
}

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

    // Step length
    double h = 1.0 / (n);

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
    cout << "Matrix vectors, b, c, a" << endl;
    for (int i = 1; i < n+1; i++) {
        cout << a[i] << " " << b[i] << " " << c[i] << endl;
    }

    // construction b_tilde
    double* b_tilde = new double[n+1];

    // computing and printing b_tilde
    cout << "B_tilde" << endl;

    b_tilde[1] = b[1];
    cout << b_tilde[1] << endl;

    for (int i = 2; i < n+1; i++) {
        b_tilde[i] = b[i] - ((a[i] * c[i-1]))/(b_tilde[i-1]);
        cout << b_tilde[i] << endl;
    }

    // Now the effs
    double* f_tilde = new double[n+1];
    double* f = new double[n+1];

    // x values?
    cout << "x values" << endl;
    double* x = new double[n];
    for (int i = 1; i < n+1; i++) {
        x[i] = (i-1) * h;
        cout << x[i] << endl;
    }

    // Computing the real effs
    cout << "Real effs" << endl;
    for (int i = 1; i < n+1; i++) {
        f[i] = RHS(x[i]);
        cout << f[i] << endl;
    }

    // the other effs
    cout << "f_tilde" << endl;
    f_tilde[1] = f[1];
    for (int i = 2; i < n+1; i++) {
        f_tilde[i] = f[i] - ((a[i] * f_tilde[i-1]))/(b_tilde[i-1]);
        cout << f_tilde[i] << endl;
    }

    return 0;
}
