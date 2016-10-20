#include "examples.h"
#include "system.h"
#include "particle.h"
#include "Integrators/eulercromer.h"
#include "Integrators/velocityverlet.h"
#include "Potentials/newtoniangravity.h"
#include "Potentials/nopotential.h"
#include "InitialConditions/twobody.h"
#include "InitialConditions/threebody.h"
#include "InitialConditions/multibody.h"

#include <iostream>
#include <cmath>


void Examples::twoBodyProblem() {
    double G = 4*M_PI*M_PI; // 6.67E-11 Nm/kg adjusted to correct units

    System* twoBodySystem = new System();
    twoBodySystem->setIntegrator        (new EulerCromer(twoBodySystem));
    twoBodySystem->setPotential         (new NewtonianGravity(G));
    twoBodySystem->setInitialCondition  (new TwoBody());
    twoBodySystem->setFileWriting       (true);
    twoBodySystem->removeLinearMomentum ();
    twoBodySystem->integrate            (10000);
}

void Examples::threeBodyProblem() {
    double G = 4*M_PI*M_PI;

    System* threeBodySystem = new System();
    threeBodySystem->setIntegrator        (new VelocityVerlet(threeBodySystem));
    threeBodySystem->setPotential         (new NewtonianGravity(G));
    threeBodySystem->setInitialCondition  (new ThreeBody());
    threeBodySystem->setFileWriting       (true);
    threeBodySystem->removeLinearMomentum ();
    threeBodySystem->integrate            (30000);
}

void Examples::multiBodyProblem() {
    double G = 4*M_PI*M_PI; //6.67e-11;

    System* multiBodySystem = new System();
    multiBodySystem->setIntegrator        (new VelocityVerlet(multiBodySystem));
    multiBodySystem->setPotential         (new NewtonianGravity(G));
    multiBodySystem->setInitialCondition  (new MultiBody());
    multiBodySystem->setFileWriting       (true);
    multiBodySystem->removeLinearMomentum ();
    multiBodySystem->integrate            (100000);
}
