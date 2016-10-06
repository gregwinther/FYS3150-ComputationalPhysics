#pragma once
#include "particle.h"
#include "potential.h"
#include <string>

class NewtonianGravity : public Potential {
private:
    double m_G;

public:
    NewtonianGravity(double G);
    void computeForces(Particle& a, Particle& b);
    std::string getName();
};
