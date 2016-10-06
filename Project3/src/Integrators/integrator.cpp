#include "integrator.h"
#include "../system.h"

Integrator::Integrator(System* system) {
    m_system = system;
}

void Integrator::setDt(double dt) {
    m_dt = dt;
}

std::string Integrator::getName() {
    return "Unknown";
}
