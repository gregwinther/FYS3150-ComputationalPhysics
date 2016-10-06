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

    Particle* largeBody = new Particle(vec3(0,0,0), vec3(0,0,0), 1.0);
    Particle* smallBody = new Particle(vec3(1,0,0), vec3(0,1,0), 0.1);
    system.addParticle(largeBody);
    system.addParticle(smallBody);
}

std::string TwoBody::getName() {
    return "Two-body";
}
