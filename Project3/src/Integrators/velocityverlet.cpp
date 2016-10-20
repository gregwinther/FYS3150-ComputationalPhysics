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

    m_system->computeForces();
    for (int i = 1; i < particles.size(); i++) {
        Particle *p = particles.at(i);

        vec3 a = (p->getForce()) / (p->getMass());

        p->getPosition() += p->getVelocity()*m_dt + (1.0/2)*a*m_dt*m_dt;

        m_system->computeForces();
        vec3 anew = (p->getForce()) / (p->getMass());

        p->getVelocity() += (a + anew) * (1.0/2) * m_dt;
    }
}
