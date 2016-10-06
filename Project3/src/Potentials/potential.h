#pragma once
#include "../particle.h"
#include <string>

class Potential {
protected:
    double m_potentialEnergy = 0;

public:
    Potential() {}
    virtual void computeForces(Particle& a, Particle& b) = 0;
    virtual std::string getName();
    void   resetPotentialEnergy() { m_potentialEnergy = 0; }
    double getPotentialEnergy()   { return m_potentialEnergy; }
};
