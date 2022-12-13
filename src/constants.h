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
        const float deltaTimeDefault = 0.1;
    }

    namespace lane
    {
        const float limitVelocityDefault = 130.;
        const float lengthDefault = 2000;
        const float vehiclesPerMinuteDefault = 10.;
    }

    namespace vehicle
    {
        const int factoryFactorMinDefault = 75;
        const int factoryFactorMaxDefault = 125;
    }

    namespace car
    {
        const float lengthDefault = 5.;
        const float decelerationDefault = 15.;
        const float accelerationDefault = 5.;
        const float brakingDistanceFactorDefault = 2.5;
        const float accelDistanceFactorDefault = 7.5;
        const Motion startMotion = Motion::Accelerating;
        const float startVelocityFactorDefault = 0.5;
        const float safeDistanceToEnterLaneFactorDefault = 2.;
    }
}

#endif