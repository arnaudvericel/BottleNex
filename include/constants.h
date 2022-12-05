#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "enums.h"

// fixme : all these constants must go to a config object at some point

namespace constants
{
    namespace sim
    {
        constexpr int nbDumps = 1000;
        constexpr float deltaTime = 0.1; // fixme : needs to be computed at each timestep with CFL condition
        constexpr float maxTime = 600.;
        constexpr float vehiclesPerMin = 30.;
    }

    namespace car
    {
        constexpr float brakingDistanceFactor = 2.5;
        constexpr float cruiseDistanceFactor = 5.;
        constexpr float accelDistanceFactor = 7.5;
        constexpr Motion startMotion = Motion::Accelerating;
        constexpr float startVelocityFactor = 0.5;
        constexpr float safeDistanceToEnterLaneFactor = 2.;
    }
}

#endif