# Studies of phase transitions in magnetic systems

In this project the widely popular Ising model is used to study phase transistions

Compilation:
```
mpic++ -std=c++11 main.cpp ising.cpp lib.cpp
```
Exectuion:
```
mpirun -n [number of threads] ./a.out [L] [T_init] [T_final] [T_step] [mc cycles]
```
