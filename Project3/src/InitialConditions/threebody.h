#pragma once
#include "../InitialConditions/initialcondition.h"
#include <string>

class ThreeBody : public InitialCondition {
public:
    ThreeBody() {}
    void setupParticles(class System& system);
    std::string getName();
};
