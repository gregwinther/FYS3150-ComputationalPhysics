#include "twobody.h"
#include "../vec3.h"
#include "../system.h"
#include <cmath>


void TwoBody::setupParticles(System &system) {
    /*
     * Here, we set up the particle system for two particles.
     * For our project we have used two of these:
     * The Sun-Earth system and
     * The Sun-Mercury system
     */

    double solar_mass 	= 1.988544 * pow(10,30);
    double mercury_mass = 3.302 * pow(10,23) / solar_mass;

    Particle* sun = new Particle(vec3(3.5554E-03,  3.4437E-03, -1.5959E-04), vec3(-2.0393E-06,  6.8258E-06,  4.1904E-08)*365.2422, 1,"Sun");
    //Particle* mercury = new Particle(vec3(-3.9067E-01, -5.3842E-02,  3.1326E-02), vec3(-1.8057E-03, -2.6625E-02, -2.0106E-03)*365.2422, mercury_mass,"Mercury");
    Particle* mercury = new Particle(vec3(0.3075, 0,0), vec3(0, 12.44, 0), mercury_mass, "Mercury");
    system.addParticle(sun);
    system.addParticle(mercury);
}

std::string TwoBody::getName() {
    return "Two-body";
}
