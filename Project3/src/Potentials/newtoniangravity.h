#pragma once
#include "particle.h"
#include "potential.h"
#include <string>
#include <cmath>

class NewtonianGravity : public Potential {
private:
    double m_G;
    double solar_mass = 1;
    double mercury_mass = 3.302 * pow(10, 23) / 1.988544*pow(10,30);
    double old_angular_momentum = 0;
    double angular_momentum = 0;

    // Set some helper variables before we start the time integration.
    double thetaPrevious 		= 0;	// The perihelion angle of the previous time step.
    double theta            	= 0;	// The perihelion angle of the current time step.

    double rPreviousPrevious 	= 0;	// Mercury-Sun-distance two times steps ago.
    double rPrevious         	= 0;	// Mercury-Sun-distance of the previous time step.
    double r                 	= 0;	// Mercury-Sun-distance of the current time step.


public:
    NewtonianGravity(double G);
    void computeForces(Particle& a, Particle& b);
    std::string getName();
};
