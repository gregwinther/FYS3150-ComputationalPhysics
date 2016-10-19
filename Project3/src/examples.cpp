#include "examples.h"
#include "system.h"
#include "particle.h"
#include "Integrators/eulercromer.h"
#include "Integrators/velocityverlet.h"
#include "Potentials/newtoniangravity.h"
#include "Potentials/nopotential.h"
#include "InitialConditions/twobody.h"
#include "InitialConditions/threebody.h"
#include <iostream>
#include <cmath>


void Examples::twoBodyProblem() {
    double G = 1.0;

    System* twoBodySystem = new System();
    twoBodySystem->setIntegrator        (new EulerCromer(twoBodySystem));
    twoBodySystem->setPotential         (new NewtonianGravity(G));
    twoBodySystem->setInitialCondition  (new TwoBody());
    twoBodySystem->setFileWriting       (true);
    twoBodySystem->removeLinearMomentum ();
    twoBodySystem->integrate            (5000);
}

void Examples::threeBodyProblem() {
    /*
     * This is where you should set up a three-body problem, using the
     * InitialCondition::ThreeBody class as System's InitialCondition.
     *
     * You should start by considering the two-body case in
     * Examples::twoBodyProblem, before continuing with this more complicated
     * case.
     */
}
