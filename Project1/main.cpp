#include "problems.h"
#include <math.h>
#include <iostream>

int main(int argc, char* args[]) {

    int n = 10;

    if (argc > 1) {
        n = atof(args[1]);
    }

    //problem1ab(n);
    problem1c(n);
    //problem1e(n);

    return 0;
}
