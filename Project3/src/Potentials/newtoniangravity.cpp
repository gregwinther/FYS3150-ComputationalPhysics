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
     * calculating the potential energy, V(r) WHY? WHY?, it is assumed by the Potential
     * class that this quantity is calculated here and added to the
     * m_potentialEnergy variable. Note: You may skip this until you have a
     * working two-body problem, since the calculation of the potential energy
     * is only neccessary for verification purposes later.
     */

    // Aquiring data
    vec3 r_a = a.getPosition();
    vec3 r_b = b.getPosition();
    double m_a = a.getMass();
    double m_b = b.getMass();
    vec3 r = r_a - r_b;

    // FORCE COMPUTATION

    // Computing force components for particle a
    vec3 F;

    // x-direction
    F = -((m_G*m_a*m_b) / (r.lengthSquared()*r.length())) * r;

    double V = -(m_G*m_a*m_b) / r.length();
    m_potentialEnergy += V;

    // Adding force to particle a
    a.addForce(F[0], F[1], F[2]);
    // Force acting on particle b acts in opposite direction (N3L)
    b.addForce(-F[0], -F[1], -F[2]);
}

std::string NewtonianGravity::getName() {
    return "Newtonian gravity";
}
