#pragma once
#include <vector>
#include <string>
#include "../particle.h"

class Integrator {
protected:
    double          m_dt        = 1e-3;
    class System*   m_system    = nullptr;

public:
    Integrator(class System* system);
    void setDt(double dt);
    double getDt() { return m_dt; }
    virtual std::string getName();
    virtual void integrateOneStep(std::vector<Particle*> particles) = 0;
};
