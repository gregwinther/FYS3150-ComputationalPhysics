#include "multibody.h"
#include "../vec3.h"
#include "../system.h"
#include <cmath>

void MultiBody::setupParticles(System &system) {

    // Units in AU and mass as fraction of sun
    double solar_mass 	= 1.988544 * pow(10, 30);
    double mercury_mass = 3.302 * pow(10, 23) / solar_mass;
    double venus_mass 	= 48.685 * pow(10, 23) / solar_mass;
    double earth_mass 	= 5.97219 * pow(10, 24) / solar_mass;
    double mars_mass 	= 6.4185 * pow(10, 23) / solar_mass;
    double jupiter_mass = 1898.13 * pow(10, 24) / solar_mass;
    double saturn_mass	= 5.68319 * pow(10, 26) / solar_mass;
    double uranus_mass  = 86.8103 * pow(10, 24) / solar_mass;
    double neptune_mass = 102.41 * pow(10, 24) / solar_mass;
    double pluto_mass	= 1.307 * pow(10, 22) / solar_mass;
    double moon_mass 	= 734.9 * pow(10,20) / solar_mass;


    Particle *sun = new Particle(vec3(3.5554E-03,  3.4437E-03, -1.5959E-04), vec3(-2.0393E-06,  6.8258E-06,  4.1904E-08)*365.2422, 1, "Sun");
    Particle *mercury = new Particle(vec3(-3.9067E-01, -5.3842E-02, 3.1326E-02), vec3(-1.8057E-03, -2.6625E-02, -2.0106E-03)*365.2422, mercury_mass, "Mercury");
    Particle *venus = new Particle(vec3(2.9535E-01, -6.6297E-01, -2.6135E-02), vec3(1.8390E-02,  8.0510E-03, -9.5100E-04)*365.2422, venus_mass, "Venus");
    Particle *earth = new Particle(vec3(8.9232E-01,  4.5238E-01, -1.808E-04), vec3(-8.0392E-03,  1.5299E-02, -4.9539E-07)*365.2422, earth_mass, "Earth");
    Particle *mars = new Particle(vec3( 1.2012, -6.8454E-01, -4.3970E-02), vec3(7.5008E-03,  1.3339E-02,  9.5301E-05)*365.2422, mars_mass, "Mars");
    Particle *jupiter = new Particle(vec3(-5.4257, -4.8938E-01,  1.2337E-01), vec3(5.9024E-04, -7.1587E-03,  1.6542E-05)*365.2422, jupiter_mass, "Jupiter");
    Particle *saturn = new Particle(vec3(-2.2413,-9.7811703,  2.5927E-01), vec3(5.1320E-03, -1.2636E-03, -1.8228E-04)*365.2422, saturn_mass, "Saturn");
    Particle *uranus = new Particle(vec3(1.8455E+01,  7.5787E+00, -2.1094E-01), vec3(-1.5228E-03,  3.4549E-03,  3.2562E-05)*365.2422, uranus_mass, "Uranus");
    Particle *neptune = new Particle(vec3(2.82E+01, -9.9073, -4.4739E-01), vec3(1.0174E-03,  2.9810E-03, -8.4837E-05)*365.2422, neptune_mass, "Neptune");
    Particle *pluto = new Particle(vec3(9.4392, -3.1817E+01,  6.7423E-01), vec3(3.0745E-03,  2.4227E-04, -9.1527E-04)*365.2422, pluto_mass, "Pluto");
    Particle *moon = new Particle(vec3(8.839E-01,  4.7004E-01, -3.8302E-04), vec3(-8.9075E-03,  1.5148E-02,  1.7999E-05)*365.2422, moon_mass, "Moon");

    system.addParticle(sun);
    system.addParticle(mercury);
    system.addParticle(venus);
    system.addParticle(earth);
    system.addParticle(mars);
    system.addParticle(jupiter);
    system.addParticle(saturn);
    system.addParticle(uranus);
    system.addParticle(neptune);
    system.addParticle(pluto);
    system.addParticle(moon);
}

std::string MultiBody::getName() {
    return "Multi-body";
}
