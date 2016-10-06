#pragma once
#include "integrator.h"
#include "../particle.h"
#include <vector>

class EulerCromer : public Integrator {
public:
    EulerCromer(class System* system);
    void integrateOneStep(std::vector<Particle*> particles);
    std::string getName();
};
