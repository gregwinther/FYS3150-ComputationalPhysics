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

    r_a.print();
    r_b.print();

    // FORCE COMPUTATION

    // Computing force components for particle a
    double dFx, dFy, dFz;

    // x-direction
   if (r_a[0] > r_b[0]) {
        dFx = -(m_G*m_a*m_b) / (r.lengthSquared());
    } else {
        dFx =  (m_G*m_a*m_b) / (r.lengthSquared());
    }

    // y-direction
   if (r_a[1] > r_b[1]) {
        dFy = -(m_G*m_a*m_b) / (r.lengthSquared());
    } else {
        dFy =  (m_G*m_a*m_b) / (r.lengthSquared());
    }

    // z-direction
   if (r_a[2] >= r_b[2]) {
        dFz = -(m_G*m_a*m_b) / (r.lengthSquared());
    } else {
        dFz =  (m_G*m_a*m_b) / (r.lengthSquared());
    }

    // ...
    //m_potentialEnergy += V;

    //std::cout << "Force computation: " << std::endl;
    //std::cout << dFx << dFy << dFz << std::endl;

    // Adding force to particle a
    a.addForce(dFx, dFy, dFz);
    // Force acting on particle b acts in opposite direction (N3L)
    b.addForce(-dFx, -dFy, -dFz);
}

std::string NewtonianGravity::getName() {
    return "Newtonian gravity";
}
