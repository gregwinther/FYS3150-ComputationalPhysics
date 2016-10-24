#include "threebody.h"
#include "../vec3.h"
#include "../system.h"
#include <cmath>


void ThreeBody::setupParticles(System &system) {
    /*
     * Here, we set uo the particle system for three particles.
     * For our project we have one such system:
     * The Sun-Earth-Jupiter system
     */

    double solar_mass   = 1.988544 * pow(10,30);
    double earth_mass 	= 5.97219  * pow(10, 24) / solar_mass;
    double jupiter_mass = 1898.13  * pow(10, 24) / solar_mass;

    Particle* sun = new Particle(vec3(0,0,0), vec3(0,0,0), 1.0, "Sun");
    Particle* earth = new Particle(vec3(1,0,0), vec3(0,2*M_PI,0), earth_mass, "Earth");
    Particle* jupiter = new Particle(vec3(5.2,0,0), vec3(5.9024E-04, -7.1587E-03, 1.6542E-05)*365.2422, jupiter_mass, "Jupiter");

    system.addParticle(sun);
    system.addParticle(earth);
    system.addParticle(jupiter);
}

std::string ThreeBody::getName() {
    return "Three-body";
}
