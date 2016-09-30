#ifndef JACOBIMETHOD_H
#define JACOBIMETHOD_H

double maxOffDiagonals(arma::mat &A, int &k, int &l, int n,double Omega_r);
void jacobiRotation(arma::mat &A, arma::mat &R, int &k, int &l, int n);
void jacobiMethod(arma::mat &A, arma::mat &R, int n);
void jacobiEigTest(arma::mat &A, arma::mat &R, int n);
arma::mat constructA(double &rho_min, double &rho_max,int n,int interacting);
void jacobiOrthogTest(arma::mat &A,arma::mat &R,int n);
void tests(arma::mat &A,arma::mat &R,int n);
void jacobiMaxoffTest(arma::mat &A,int n);
void writeToFile(double rho_max , double rho_min, int n, arma::mat &R,double Omega_r,int lowestvalueindex);

#endif // JACOBIMETHOD_H
