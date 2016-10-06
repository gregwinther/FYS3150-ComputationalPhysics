#include "newtoniangravity.h"
#include <iostream>

NewtonianGravity::NewtonianGravity(double G) : m_G(G) {

}

void NewtonianGravity::computeForces(Particle& a, Particle& b) {
    /*
     * This is where the ordinary Newtoninan gravity forces and potential
     * energies should be calculated. This method is called by the System
     * class in System::computeForces, for all particle pairs a and b.
     *
     * Note that you may access the mass and the position of the particles a
     * and b by
     *
     *      a.getMass();       b.getMass();
     *      a.getPosition();   b.getPosition();
     *
     * In order to apply the forces to each particle, it is easiest to use the
     * Particle::addForce method.
     *
     * Since calculating the forces between a and b almost inevitably involves
     * calculating the potential energy, V(r), it is assumed by the Potential
     * class that this quantity is calculated here and added to the
     * m_potentialEnergy variable. Note: You may skip this until you have a
     * working two-body problem, since the calculation of the potential energy
     * is only neccessary for verification purposes later.
     */

    // ...
    //m_potentialEnergy += V;
    //a.addForce(dFx, dFy, dFz);
    //b.addForce(...);
}

std::string NewtonianGravity::getName() {
    return "Newtonian gravity";
}
