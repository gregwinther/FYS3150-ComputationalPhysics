#ifndef JACOBIMETHOD_H
#define JACOBIMETHOD_H

double maxOffDiagonals(arma::mat &A, int &k, int &l, int n,double Omega_r);
void jacobiRotation(arma::mat &A, arma::mat &R, int &k, int &l, int n);
void jacobiMethod(arma::mat &A, arma::mat &R, int n);
arma::mat constructA(double &rho_min, double &rho_max,int n, bool interacting, double omega_r);

void writeToFile(double rho_max , double rho_min, int n, arma::mat &R,double Omega_r,int lowestvalueindex);

void jacobiEigTest();
void jacobiMaxOffTest();
void jacobiOrthogTest();

#endif // JACOBIMETHOD_H
