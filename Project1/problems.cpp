#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <new>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <chrono>

#include <armadillo>

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
    auto start = chrono::high_resolution_clock::now();

    // Linspace
    for (int i=0; i<n+2; i++) {
        x[i] = i*h;
        a_vec[i] = -1;
        b_vec[i] = 2;
        c_vec[i] = -1;
    }

    // Contructing 'matrix'
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
    auto finish = chrono::high_resolution_clock::now();

    // Printing time elapsed
    cout << "Elapsed time, tridiagonal Gaussian: ";
    cout << chrono::duration_cast<chrono::nanoseconds>(finish-start).count()/pow(10,9) << " seconds" << endl;

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
    auto start = chrono::high_resolution_clock::now();

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
    auto finish = chrono::high_resolution_clock::now();
    cout << "Elapsed time, optimized tridiag Gaussion elim.: ";
    cout << chrono::duration_cast<chrono::nanoseconds>(finish-start).count()/pow(10,9)<< " seconds"<< endl;

    //Calculating relative error
    double eps[n+2];
    for (int i=2; i<n+1; i++){
        eps[i] = log10(abs((v[i]-u[i])/u[i]));
    }
    //Finding maximum element in error array
    double max = eps[0];
    for (int i; i<n; i++){
        if(abs(eps[i])>abs(max)) max=eps[i];
    }
    //Printing max rel. error
    cout << "n= "<< n << endl;
    cout << "log10(h): "<< log10(h) <<endl;
    cout << "Max rel. err.: " << max <<endl;


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

void problem1e(int n){

    arma::mat A = arma::zeros<arma::mat>(n+2,n+2);
    arma::vec a(n+2); a.fill(-1);
    arma::vec b(n+2); b.fill(2);
    arma::vec c(n+2); c.fill(-1);
    arma::vec x(n+2);
    arma::vec f(n+2);
    double h = 1.0/(n+1.0);

    //Constructing the Tridiagonal A
    for (int i = 0; i < n+2; i++) {
        if (i > 0)   A(i, i-1) = a(i);
                 A(i, i)   = b(i);
        if (i < n+1) A(i, i+1) = c(i);
    }


    for (int i=0; i<n+2; i++) {
        x[i] = i*h; //linspace
        f[i] = h*h*input_func(x[i]);
    }


    // Registering start time
    auto start = chrono::high_resolution_clock::now();

    // solve Av = f
    arma::vec v = arma::solve(A,f);

    // find LU decomp of
    arma::mat L, U;
    arma::lu(L,U,A);

    // Register finish time
    auto finish = chrono::high_resolution_clock::now();
    cout << "Elapsed time LU decomposition: ";
    cout << chrono::duration_cast<chrono::nanoseconds>(finish-start).count()/pow(10,9)<< " seconds"<< endl;

    // Test of LU decomposition
    /*
    // print A,v,f
    A.print("A=");
    v.print("v =");
    f.print("f=");
    // print l
    L.print(" L= ");
    // print U
    U.print(" U= ");
    //Check that A = LU
    (A-L*U).print("Test of LU decomposition");
    */
}

