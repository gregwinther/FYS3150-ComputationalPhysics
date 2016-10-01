# Project 2 - Computational Physics
## Solving the Schrödinger equation for two electronss in a harmonic oscillator well

The armadillo library must be included in compilation. Example: `g++ main.cpp -o schrodinger.x -larmadillo`. Alternatively, a .pro file is included in the respository, so one can build and compile in Qt Creator. 

Running the program without any command line arguments will automaticall run the unit tests implemented in the program. Additionally, this will provide instructions for usage. Example: `./schrodinger.x` will yield 

```bash
AUTOMATIC TESTING: 

TEST: Calculating known eigenvalues.. SUCCESS!

TEST: Finding maximum off-diagonal value.. SUCCESS!

TEST: Orthogonality preservation..  SUCCESS!


General Usage:
 ./schrodinger.x n rho_max Coulomb omega_r output_filename
```
Example of usage: `./schrodinger.x 250 5 1 0.1 data.txt`
