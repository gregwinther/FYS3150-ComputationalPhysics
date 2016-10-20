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
         * This is where you need to update the positions and the velocities
         * and the velocities of each particle according to the Euler-Cromer
         * scheme.
         *
         * You can access the position of particle number i by
         *
         *      p->getPosition()
         *
         * Remember that the positions and velocities of all the particles are
         * vec3 vectors, which you can use the +=, -=, etc. operators on.
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
