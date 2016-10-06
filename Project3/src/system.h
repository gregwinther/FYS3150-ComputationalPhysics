#pragma once
#include "particle.h"
#include <vector>
#include <fstream>

class System {
private:
    bool                        m_writeToFile       = false;
    bool                        m_outFileOpen       = false;
    int                         m_integrateSteps    = 0;
    int                         m_numberOfParticles = 0;
    double                      m_kineticEnergy     = 0;
    double                      m_totalEnergy       = 0;
    double                      m_potentialEnergy   = 0;
    class Integrator*           m_integrator        = nullptr;
    class Potential*            m_potential         = nullptr;
    class InitialCondition*     m_initialCondition  = nullptr;
    std::ofstream               m_outFile;
    std::vector<Particle*>      m_particles;

public:
    System() {}
    void computeForces          ();
    void resetAllForces         ();
    void setPotential           (class Potential* potential);
    void setIntegrator          (class Integrator* integrator);
    void setInitialCondition    (class InitialCondition* initialCondition);
    void setDt                  (double dt);
    void integrate              (int numberOfSteps);
    void addParticle            (Particle* p);
    void printIntegrateInfo     (int stepNumber);
    void removeLinearMomentum   ();
    void setFileWriting         (bool writeToFile);
    void writePositionsToFile   ();
    void closeOutFile           ();
    double computeKineticEnergy ();
};

