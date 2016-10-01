#include <iostream>
#include <math.h>
#include <armadillo>
#include <string>
#include <ctime>

#include "jacobimethod.h"
#include "jacobiMethod.cpp"


using namespace std;

int main(int argc, char *argv[])
{  /*
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    cout << argv[3] << endl;
    cout << argv[4] << endl;
    cout << argv[5] << endl;
    cout << argc << endl;
    */

    if (argc != 6) {
        cout << "AUTOMATIC TESTING: \n"  << endl;
        jacobiEigTest();
        jacobiMaxOffTest();
        jacobiOrthogTest();

        cout << "\nGeneral Usage:\n " << argv[0]
             << " n" << " rho_max" << " Coulomb"
             << " omega_r" << " output_filename\n"
             << endl;
    } else {

        cout << "Computing. Please wait." << endl;

        // Parsing n
        int n = atoi(argv[1]);

        // Parsing rho_max and declaring rho_min
        // This is the dimensionless radial component
        double rho_min = 0.0;
        double rho_max = atof(argv[2]);

        // Coulomb interaction?
        bool interacting = (bool) atoi(argv[3]);

        // Parsing angular momentum
        double omega_r = atof(argv[4]);

        // Parsing output filename
        string output_file = argv[5];

        // Declaring and initializing matrices
        arma::mat A(n,n);
        arma::mat R; R.eye(n,n);

        // Ground state index
        int minIndex;

        // Timer start
        clock_t start = clock();

        // Constructing second derivative approximation matrix
        A = constructA(rho_min, rho_max, n, interacting, omega_r);

        // Computing ..
        jacobiMethod(A, R, n, minIndex);

        // Writing data to file
        writeToFile(R, n, output_file, minIndex);

        // Timer stop
        clock_t stop = clock();

        cout << "Computation finished. Elapsed time: ";
        cout << ( stop - start ) / (double) CLOCKS_PER_SEC << " seconds" << endl;
        cout << "Data written to " << output_file.c_str() << "\n" << endl;
    }

}
