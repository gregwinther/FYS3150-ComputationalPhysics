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
     * The velocity Verlet scheme
     */

    m_system->computeForces();
    for (int i = 1; i < particles.size(); i++) {
        Particle *p = particles.at(i);

        // Acceleration vector
        vec3 a = (p->getForce()) / (p->getMass());

        // Position update
        p->getPosition() += p->getVelocity()*m_dt + (1.0/2)*a*m_dt*m_dt;

        // Recomputing forces to get new acceleration
        m_system->computeForces();

        // New acceleration vector
        vec3 anew = (p->getForce()) / (p->getMass());

        // Velocity update
        p->getVelocity() += (a + anew) * (1.0/2) * m_dt;
    }
}
