#include "twobody.h"
#include "../vec3.h"
#include "../system.h"
#include <cmath>


void TwoBody::setupParticles(System &system) {
    /*
     * Here, two bodies are created at a distance r=1.0 apart from eachother.
     * A heavy body is placed in the origin, while a lighter body is placed
     * in (1,0,0) with an initial velocity of (0,1,0). The larger body is given
     * a mass of 1.0, while the mass of the smaller body is set to 0.1.
     *
     * Please note that these are NOT the values needed in order to achieve a
     * circular orbit (Sun-Earth-like). It is up to you to find the correct
     * masses, distances, and velocities.
     *
     * Note that the constructor of the Particle class takes three inputs,
     * a vec3-vector of positions values, a vec3-vector of velocity values,
     * and the mass--a double. As an example:
     *
     *      Particle* p = new Particle(vec3(1,2,3), vec3(4,5,6), 7.0);
     *                                  ^            ^            ^
     *                               Position     Velocity      Mass
     */

    double solar_mass 	= 1.988544 * pow(10,30);
    double mercury_mass = 3.302 * pow(10,23) / solar_mass;

    Particle* sun = new Particle(vec3(3.5554E-03,  3.4437E-03, -1.5959E-04), vec3(-2.0393E-06,  6.8258E-06,  4.1904E-08)*365.2422, 1,"Sun");
    Particle* mercury = new Particle(vec3(-3.9067E-01, -5.3842E-02,  3.1326E-02), vec3(-1.8057E-03, -2.6625E-02, -2.0106E-03)*365.2422, mercury_mass,"Mercury");
    system.addParticle(sun);
    system.addParticle(mercury);
}

std::string TwoBody::getName() {
    return "Two-body";
}
