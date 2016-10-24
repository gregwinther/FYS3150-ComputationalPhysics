#include "newtoniangravity.h"
#include <iostream>
#include <string>
#include <iomanip>

using std::setprecision;

NewtonianGravity::NewtonianGravity(double G) : m_G(G) {

}

void NewtonianGravity::computeForces(Particle& a, Particle& b) {
    /*
     * This is where the ordinary Newtoninan gravity forces and potential
     * energies should be calculated. This method is called by the System
     * class in System::computeForces, for all particle pairs a and b.
     */

    // Aquiring data
    vec3 r_a = a.getPosition();
    vec3 r_b = b.getPosition();
    double m_a = a.getMass();
    double m_b = b.getMass();
    vec3 r = r_a - r_b;

    old_angular_momentum = angular_momentum;

    // FORCE COMPUTATION
    vec3 F;
    F = -((m_G*m_a*m_b) / (r.lengthSquared()*r.length())) * r;

    // Angular momentum
        vec3 v = b.getVelocity();
        vec3 l = r.cross(v);
        double l2 = l.lengthSquared();

        //Checking if angular momentum conserved
        angular_momentum = l2;
        double angdiff = fabs(old_angular_momentum-angular_momentum);
        if ( angdiff > 1e-5){
            //std::cout << setprecision(7) <<"Angular momentum not conserved " << angdiff<< std::endl;
        }

        // Potential energy
        m_potentialEnergy -= (m_G*m_a*m_b) / r.length();

        // Force with Mercury correction
        if ( (a.getName().compare("Sun") == 0) && (b.getName().compare("Mercury") == 0 )) {
            double c = 63239.7263; // [AU per year]
            double correction = 1+(3.0*l2)/(c*c*r.lengthSquared());
            F *= correction;
        }

    // Adding force to particle a
    a.addForce(F[0], F[1], F[2]);
    // Force acting on particle b acts in opposite direction (N3L)
    b.addForce(-F[0], -F[1], -F[2]);
}

std::string NewtonianGravity::getName() {
    return "Newtonian gravity";
}
