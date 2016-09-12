#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <time.h>

using namespace std;
ofstream ofile;

double analytic_solution(double x) {
    return 1.0-(1-exp(-10))*x-exp(-10*x);
}

double input_func(double x) {
    return 100*exp(-10*x);
}

void problem1ab(int n)
{

    /* ALLOCATING MEMORY AND INITIALISING VARIABLES
     * Allocating n+2 spaces, the first and last index
     * are for the boundary conditions
     */

    // Timer variables
    clock_t start, finish;

    // Diagonals of matrix
    double *a_vec = new double[n+2];
    double *b_vec = new double[n+2];
    double *c_vec = new double[n+2];

    // Analytical solution
    double *u = new double[n+2];
    // Numerical solution
    double *v = new double[n+2];

    // Step size
    double h = 1.0/(n+1.0);

    // Steps
    double *x = new double[n+2];

    // RHS
    double *f = new double[n+2];
    double *f_tilde = new double[n+2];

    // Saving start time
    start = clock();

    // Linspace
    for (int i=0; i<n+2; i++) {
        x[i] = i*h;
        a_vec[i] = -1;
        b_vec[i] = 2;
        c_vec[i] = -1;
    }

    // Contruction 'matrix'
    for (int i=0; i<n+2; i++) {
        f[i] = h*h*input_func(x[i]);
        u[i] = analytic_solution(x[i]);
    }

    // GAUSSIAN ELIMINATION
    // Forward substitution
    f_tilde[1] = f[1];
    for (int i=2;i<n+1;i++){
       // Updating right hand side of matrix equation:
       b_vec[i] = b_vec[i]-a_vec[i]*c_vec[i-1]/b_vec[i-1];
       f_tilde[i] = f[i] - a_vec[i]*f_tilde[i-1]/b_vec[i-1];
    }

    // Backward substition:
    v[n] = f_tilde[n]/b_vec[n];
    for (int i=n-1;i>=1;i--){
        v[i] = (f_tilde[i]-c_vec[i]*v[i+1])/b_vec[i];
    }

    // Register stop time
    finish = clock();

    // Printing time elapsed
    cout << "Elapsed time: ";
    cout << ((double) (finish - start) / CLOCKS_PER_SEC) << endl;

    // Open file and write results to file:
    ofile.open("dataproj1ab.txt");
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << n << endl;
    ofile << "       x:             u(x):          v(x):  " << endl;
    for (int i=0;i<n+2;i++) {
       ofile << setw(15) << setprecision(8) << x[i];
       ofile << setw(15) << setprecision(8) << u[i];
       ofile << setw(15) << setprecision(8) << v[i] << endl;
    }

    ofile.close();

    delete [] a_vec;
    delete [] b_vec;
    delete [] c_vec;
    delete [] u;
    delete [] v;
    delete [] x;
    delete [] f;
    delete [] f_tilde;
}

int problem1c(int n)
{

    /* ALLOCATING MEMORY AND INITIALISING VARIABLES
     * Allocating n+2 spaces, the first and last index
     * are for the boundary conditions
     */

    //Declaring time variable
    clock_t start, finish;

    // Diagonal of matrix
    double *b_vec = new double[n+2];

    // Analytical solution
    double *u = new double[n+2];
    // Numerical solution
    double *v = new double[n+2];

    // Step size
    double h = 1.0/(n+1.0);

    // Steps
    double *x = new double[n+2];

    // RHS
    double *f = new double[n+2];
    double *f_tilde = new double[n+2];

    //Start timing
    start = clock();

    // Contructing 'matrix'
    for (int i=0; i<n+2; i++) {
        x[i] = i*h; //linspace
        f[i] = h*h*input_func(x[i]);
        u[i] = analytic_solution(x[i]);
        b_vec[i] = 2;
    }

    // GAUSSIAN ELIMINATION
    // Forward substitution
    f_tilde[1] = f[1];
    for (int i=2;i<n+1;i++){
       // Updating right hand side of matrix equation:
       b_vec[i] -= 1/b_vec[i-1];
       f_tilde[i] = f[i] +f_tilde[i-1]/b_vec[i-1];
    }

    // Backward substition:
    v[n] = f_tilde[n]/b_vec[n];
    for (int i=n-1;i>=1;i--){
        v[i] = (f_tilde[i]+v[i+1])/b_vec[i];
    }
    //Finish timing
    finish = clock();
    cout << "Elapsed time: ";
    cout << ((double) (finish - start)/CLOCKS_PER_SEC) << endl;


    // Open file and write results to file:
    ofile.open("dataproj1c.txt");
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << n << endl;
    ofile << "       x:             u(x):          v(x):  " << endl;
    for (int i=0;i<n+2;i++) {
       ofile << setw(15) << setprecision(8) << x[i];
       ofile << setw(15) << setprecision(8) << u[i];
       ofile << setw(15) << setprecision(8) << v[i] << endl;
    }

    ofile.close();

    delete [] b_vec;
    delete [] u;
    delete [] v;
    delete [] x;
    delete [] f;
    delete [] f_tilde;

    return 0;
}
