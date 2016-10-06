#include "velocityverlet.h"
#include "../system.h"

VelocityVerlet::VelocityVerlet(System* system)
    : Integrator(system) {
}

std::string VelocityVerlet::getName() {
    return "Velocity verlet";
}

void VelocityVerlet::integrateOneStep(std::vector<Particle*> particles) {
    /*
     * This is where you should implement the Velocity Verlet algorithm.
     *
     * You should start by impelmenting the Euler-Cromer scheme in the
     * Integrator::EulerCromer class, and then implement the more complicated
     * Velocity Verlet algorithm only after you have a working implementation
     * of Euler-Cromer.
     */
}
