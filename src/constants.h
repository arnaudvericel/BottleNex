#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

#include "enums.h"

namespace constants
{
    namespace files
    {
        const std::string extension = ".dat";
    }
    namespace sim
    {
        const float factorCFLDefault = 1.0;
        const int nbDumpsDefault = 1000;
        const float maxTimeMinDefault = 10.;
        const float vehiclesPerMinDefault = 15;
    }

    namespace lane
    {
        const float limitVelocityDefault = 130.;
        const float lengthDefault = 2000;
        const float vehiclesPerMinuteDefault = 10.;
    }

    namespace car
    {
        const float maxVelocityDefault = 150.;
        const float lengthDefault = 5.;
        const float decelerationDefault = 40.;
        const float accelerationDefault = 10.;
        const float brakingDistanceFactorDefault = 2.5;
        const float cruiseDistanceFactorDefault = 5.;
        const float accelDistanceFactorDefault = 7.5;
        const Motion startMotion = Motion::Accelerating;
        const float startVelocityFactorDefault = 0.5;
        const float safeDistanceToEnterLaneFactorDefault = 2.;
    }
}

#endif