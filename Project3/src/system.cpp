#include "system.h"
#include "Integrators/integrator.h"
#include "Potentials/potential.h"
#include "InitialConditions/initialcondition.h"
#include "particle.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using std::cout;
using std::endl;
using std::setprecision;



void System::computeForces() {
    /*
     * Here you should sum over all particle pairs and compute the forces
     * between each one. This should be done by the Potential::computeForces
     * method which takes pointers to two Particles as input. I.e. the forces
     * between particle i and particle j should be computed by

     *      m_potential->computeForces(*m_particles.at(i), *m_particles.at(j));
     *
     * Note: It is important that you do not sum over each particle pair more
     * than once. A simple way to ensure this is done is by a double for loop,
     * one running from i=0...n, and the other running from j=i+1...n. You
     * should convince yourself that this is true before you implement this
     * loop.
     */

    resetAllForces();
    m_potential->resetPotentialEnergy();

    int n = m_numberOfParticles;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            m_potential->computeForces(*m_particles.at(i), *m_particles.at(j));
        }
    }

}

void System::resetAllForces() {
    for (int i=0; i<m_numberOfParticles; i++) {
        m_particles.at(i)->resetForces();
    }
}

void System::setPotential(Potential* potential) {
    m_potential = potential;
}

void System::setIntegrator(Integrator* integrator) {
    m_integrator = integrator;
}

void System::setInitialCondition(InitialCondition* initialCondition) {
    m_initialCondition = initialCondition;
    m_initialCondition->setupParticles(*this);
}

void System::setDt(double dt) {
    m_integrator->setDt(dt);
}

void System::integrate(int numberOfSteps) {
    m_integrateSteps = numberOfSteps;
    printIntegrateInfo(0);

    // Set some helper variables before we start the time integration.
    double thetaPrevious        = 0;	// The perihelion angle of the previous time step.
    double thetaCurrent 		= 0;	// The perihelion angle of the current time step.

    double rPreviousPrevious 	= 0;	// Mercury-Sun-distance two times steps ago.
    double rPrevious            = 0;	// Mercury-Sun-distance of the previous time step.
    double rCurrent             = 0;	// Mercury-Sun-distance of the current time step.

    for (int i=1; i<numberOfSteps+1; i++) {
        m_integrator->integrateOneStep(m_particles);
        printIntegrateInfo(i);
        writePositionsToFile();
        Particle *sun = m_particles.at(0);
        Particle *mercury = m_particles.at(1);
        // Compute the current perihelion angle, using the inverse tangent function from cmath.
        // This assumes there is a vector of planets, called m_bodies, available, in which the
        // Sun is m_bodies[0] and Mercury is m_bodies[1].
        double x = mercury->getPosition().x() - sun->getPosition().x();
        double y = mercury->getPosition().y() - sun->getPosition().y();

        thetaCurrent = atan2( y, x );

        // Compute the current Mercury-Sun distance.
        rCurrent = (sun->getPosition()-mercury->getPosition()).length();

        // Check if the *previous* time step was a minimum for the Mercury-Sun distance. I.e. check
        // if the previous distance is smaller than the current one *and* the previous previous one.
        if ( rCurrent > rPrevious && rPrevious < rPreviousPrevious ) {

             // If we are perihelion, print angle (in radians) to terminal.
             writeThetasToFile(thetaPrevious);

             // Here you should also probably write it to file for later plotting or something.
        }

        // Update the helper variables (current, previous, previousPrevious).
        rPreviousPrevious 	= rPrevious;
        rPrevious			= rCurrent;
        thetaPrevious		= thetaCurrent;
    }
    closeOutFile();
}

void System::addParticle(Particle* p) {
    m_particles.push_back(p);
    m_numberOfParticles += 1;
}

double System::computeKineticEnergy() {
    /*
     * Here, the kinetic energy of the entire system should be computed. Since
     * this is independent of the potential in use, we place this method
     * directly in the system class.
     *
     */

    m_kineticEnergy = 0;

    for (int i = 0; i < m_numberOfParticles; i++) {
        m_kineticEnergy += (1.0/2) * m_particles.at(i)->velocitySquared() * m_particles.at(i)->getMass();
    }
    return m_kineticEnergy;
}

void System::printIntegrateInfo(int stepNumber) {
    if (stepNumber == 0) {
        cout << endl
             << " STARTING INTEGRATION "    << endl
             << "-------------------------" << endl
             << "  o Number of steps:     " << m_integrateSteps << endl
             << "  o Time step, dt:       " << m_integrator->getDt() << endl
             << "  o Initial condition:   " << m_initialCondition->getName() << endl
             << "  o Number of particles: " << m_particles.size() << endl
             << "  o Potential in use:    " << m_potential->getName() << endl
             << "  o Integrator in use:   " << m_integrator->getName() << endl
             << endl;
    } else if (stepNumber % 1000 == 0) {
        m_kineticEnergy     = computeKineticEnergy();
        m_potentialEnergy   = m_potential->getPotentialEnergy();
        m_totalEnergy       = m_kineticEnergy + m_potentialEnergy;
        printf("Step: %5d    E =%10.5g   Ek =%10.5g    Ep =%10.5g\n",
               stepNumber, m_totalEnergy, m_kineticEnergy, m_potentialEnergy);
        fflush(stdout);
    }
}

void System::removeLinearMomentum() {
    /*
     * Here you should remove the total momentum of the entire system, to
     * ensure the entire system does not drift away during long integration
     * times.
     *
     * This correction is not used as velocites from NASA are sufficient
     */

    vec3 totalMomentum = vec3(0,0,0);
    for (int i = 0; i < m_numberOfParticles; i++) {
        Particle *p = m_particles.at(i);

        totalMomentum += p->getVelocity() * p->getMass();
    }
}

void System::setFileWriting(bool writeToFile) {
    m_writeToFile = writeToFile;
}

void System::writePositionsToFile() {
    if (m_outFileOpen == false) {
        m_outFile.open("../ESverletHD.dat", std::ios::out);
        m_outFileOpen = true;
    } 

    for (int i = 0; i < m_numberOfParticles; i++) {
        m_outFile << setprecision(15) << m_particles.at(i)->getPosition();
    }
    m_outFile << endl;
}

void System::writeThetasToFile(double theta) {
    if (m_outFileOpen2 == false) {
         m_outFile2.open("../thetas.dat", std::ios::out);
         m_outFileOpen2 = true;
     }
     /*
      * This is where you should print the positions of each particle to file.
     * Note that the file, "positions.dat", is already open; it is opened in
      * the above if-test the first time this method is called in
      * System::Integrate.
      *
      * Which format you choose for the data file is up to you.
      */

     m_outFile2 << setprecision(15) << theta;

     m_outFile2 << endl;
 }

void System::closeOutFile() {
    if (m_writeToFile == true) {
        m_outFile.close();
        m_outFileOpen = false;
    }
}
