#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "enums.h"

namespace constants
{
    namespace sim
    {
        constexpr int nbDumps = 1000; // fixme -> in a config object
        constexpr float deltaTime = 0.1; // fixme -> in a config object
        constexpr float maxTime = 600.; // fixme -> in a config object
    }

    namespace car
    {
        constexpr float accelDistanceFactor = 5.;
        constexpr float cruiseDistanceFactor = 10.;
        constexpr Motion startMotion = Motion::Accelerating;
        constexpr float startVelocityFactor = 0.5;
        constexpr float safeDistanceToEnterLaneFactor = 10.;
    }
}

#endif