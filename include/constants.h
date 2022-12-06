#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "enums.h"

// fixme : all these constants must go to a config object at some point

namespace constants
{
    namespace files
    {
        const std::string extension = ".dat";
    }
    namespace sim
    {
        const int nbDumps = 1000;
        const float deltaTime = 0.1; // fixme : needs to be computed at each timestep with CFL condition
        const float maxTime = 600.;
        const float vehiclesPerMin = 15;
    }

    namespace car
    {
        const float brakingDistanceFactor = 2.5;
        const float cruiseDistanceFactor = 5.;
        const float accelDistanceFactor = 7.5;
        const Motion startMotion = Motion::Accelerating;
        const float startVelocityFactor = 0.5;
        const float safeDistanceToEnterLaneFactor = 2.;
    }
}

#endif