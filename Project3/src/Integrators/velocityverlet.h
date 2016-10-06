#pragma once
#include "integrator.h"
#include "../particle.h"
#include <string>

class VelocityVerlet : public Integrator {
private:
    bool m_firstStep = true;

public:
    VelocityVerlet(class System* system);
    std::string getName();
    void integrateOneStep(std::vector<Particle*> particles);
};
