/* Project 0, FYS3150 Computational Physics */
#include <iostream>
#include <fstream>
using namespace std;

int main ()
{

	/* Writing to file */
	ofstream myfile;
	myfile.open ("data.txt");
	myfile << "Writing stuff to file.\n";
	myfile.close();
	return 0;

}