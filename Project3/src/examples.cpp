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

#include <chrono>
typedef std::chrono::high_resolution_clock Clock;


void Examples::twoBodyProblem() {
    double G = 4*M_PI*M_PI;

    System* twoBodySystem = new System();
    twoBodySystem->setIntegrator        (new VelocityVerlet(twoBodySystem));
    twoBodySystem->setPotential         (new NewtonianGravity(G));
    twoBodySystem->setInitialCondition  (new TwoBody());
    twoBodySystem->setFileWriting       (false);
    twoBodySystem->removeLinearMomentum ();
    auto t1 = Clock::now();
    twoBodySystem->integrate            (1e9);
    auto t2 = Clock::now();
    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;
}

void Examples::threeBodyProblem() {
    double G = 4*M_PI*M_PI;

    System* threeBodySystem = new System();
    threeBodySystem->setIntegrator        (new VelocityVerlet(threeBodySystem));
    threeBodySystem->setPotential         (new NewtonianGravity(G));
    threeBodySystem->setInitialCondition  (new ThreeBody());
    threeBodySystem->setFileWriting       (false);
    threeBodySystem->removeLinearMomentum ();
    threeBodySystem->integrate            (2.5e5);
}

void Examples::multiBodyProblem() {
    double G = 4*M_PI*M_PI;

    System* multiBodySystem = new System();
    multiBodySystem->setIntegrator        (new VelocityVerlet(multiBodySystem));
    multiBodySystem->setPotential         (new NewtonianGravity(G));
    multiBodySystem->setInitialCondition  (new MultiBody());
    multiBodySystem->setFileWriting       (false);
    multiBodySystem->removeLinearMomentum ();
    multiBodySystem->integrate            (1e5);
}
