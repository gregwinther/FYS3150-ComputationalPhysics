#include "eulercromer.h"
#include "../system.h"
#include <iostream>

EulerCromer::EulerCromer(System* system)
    : Integrator(system) {
}

void EulerCromer::integrateOneStep(std::vector<Particle*> particles) {
    m_system->computeForces();
    for (int i=0; i<particles.size(); i++) {
        Particle *p = particles.at(i);
        /*
         * The Euler-Cromer scheme
         */

        // Acceleration vector
        vec3 a = (p->getForce()) / (p->getMass());

        // std::cout << "Accel = "; a.print();
        // std::cout << "Mass: " << p->getMass() << std::endl;
        // std::cout << "Force: " << p->getForce() << std::endl;

        // Velocity update
        p->getVelocity() += m_dt*a;

        // Position update
        p->getPosition() += m_dt*p->getVelocity();
    }
}

std::string EulerCromer::getName() {
    return "Euler-Cromer";
}
