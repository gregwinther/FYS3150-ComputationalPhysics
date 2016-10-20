#pragma once
#include "../InitialConditions/initialcondition.h"
#include <string>


class MultiBody : public InitialCondition {
public:
    MultiBody() {}
    void setupParticles(class System& system);
    std::string getName();
};
