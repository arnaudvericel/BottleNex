#include <iostream>
#include "car.h"
#include "enums.h"
#include "constants.h"
#include "config.h"

int Car::nbActiveCars = 0;

Car::Car(Lane* lane, float initVelocityMultiplier) : Vehicle() // fixme : SetLane in vehicle constructor
{
    Config* config = Config::GetConfig();

    SetLane(lane);
    length = (*config)[Config::FloatSettings::CarLength];
    acceleration = (*config)[Config::FloatSettings::CarAcceleration];
    deceleration = (*config)[Config::FloatSettings::CarDeceleration];

    motionState = constants::car::startMotion;
    currentVelocity = initVelocityMultiplier * (*config)[Config::FloatSettings::CarStartVelocityFactor] * maxVelocity;
    //std::cout << currentVelocity << " " << currentVelocity * 3.6 << std::endl;
    nbActiveCars++;
}

Car::~Car()
{
    nbActiveCars--;
}

void Car::Brake(const float deltaTime)
{
    if (currentVelocity > 0.)
    {
        currentVelocity -= deceleration * deltaTime;
        if (currentVelocity < 0.)
        {
            currentVelocity = 0.;
        }
    }
    UpdatePosition(deltaTime);
}

void Car::Cruise(const float deltaTime)
{
    UpdatePosition(deltaTime);
}

void Car::Accelerate(const float deltaTime)
{
    if (currentVelocity < targetVelocity)
    {
        currentVelocity += acceleration * deltaTime;
        if (currentVelocity > targetVelocity)
        {
            currentVelocity = targetVelocity;
        }
    }
    UpdatePosition(deltaTime);
}

void Car::EvaluateMotionState(const float deltaTime)
{
    if (forwardVehicle != nullptr)
    {
        Config* config = Config::GetConfig();
        //
        float distanceAtNextIteration = currentVelocity * deltaTime;
        float brakingDistance = (*config)[Config::FloatSettings::CarBrakingDistanceFactor] * distanceAtNextIteration;
        float accelereationDistance = (*config)[Config::FloatSettings::CarAccelerationDistanceFactor] * distanceAtNextIteration;
        float cruisingDistance = (*config)[Config::FloatSettings::CarCruisingDistanceFactor] * distanceAtNextIteration;
        float distanceToNextVehicle = forwardVehicle->GetDistanceInLane() - distanceInLane - forwardVehicle->GetLength();

        //std::cout << deltaTime << " " << distanceAtNextIteration << " " << brakingDistance << " " << accelereationDistance << " " << cruisingDistance << " " << distanceToNextVehicle << std::endl;

        if (distanceToNextVehicle <= brakingDistance) { targetVelocity = 0.; }
        else if (distanceToNextVehicle <= cruisingDistance) { targetVelocity = forwardVehicle->GetCurrentVelocity(); }
        else if (distanceToNextVehicle > accelereationDistance) { targetVelocity = maxVelocity; }
    }
    // "first" vehicle in lane -> wants to reach maxVelocity, no forward vehicle to slow it down
    else
    {
        targetVelocity = maxVelocity;
    }

    UpdateMotionState();
}
