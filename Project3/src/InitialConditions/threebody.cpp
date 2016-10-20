#include "threebody.h"
#include "../vec3.h"
#include "../system.h"
#include <cmath>


void ThreeBody::setupParticles(System &system) {
    /*
     * This is where you should implement the initialization of a three-body
     * system.
     *
     * You should start by impelmenting the two-body scheme in the
     * InitialiCondition::TwoBody class, and then implement the more
     * complicated three-body initialization only after you have a working
     * implementation of the two-body case.
     */

    Particle *sun     = new Particle(vec3(0,0,0), vec3(0,0,0), 1.0);
    Particle *earth   = new Particle(vec3(1,0,0), vec3(0,2*M_PI,0), pow(10,-6));
    Particle *jupiter = new Particle(vec3(5.2,0,0), vec3(0,M_PI,0), pow(10, -3));

    system.addParticle(sun);
    system.addParticle(earth);
    system.addParticle(jupiter);
}

std::string ThreeBody::getName() {
    return "Three-body";
}
