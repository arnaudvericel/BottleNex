#include <iostream>
#include "../include/car.h"
#include "../include/enums.h"
#include "../include/constants.h"

int Car::nbActiveCars = 0;

Car::Car(float multiplier) : Vehicle(Length, MaxVelocity, Acceleration)
{
    motionState = constants::car::startMotion;
    currentVelocity = multiplier * constants::car::startVelocityFactor * maxVelocity;
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
        currentVelocity -= acceleration * deltaTime;
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
        float distanceAtNextIteration = currentVelocity * deltaTime;
        float brakingDistance = constants::car::brakingDistanceFactor * distanceAtNextIteration;
        float accelereationDistance = constants::car::accelDistanceFactor * distanceAtNextIteration;
        float cruisingDistance = constants::car::cruiseDistanceFactor * distanceAtNextIteration;
        float distanceToNextVehicle = forwardVehicle->GetDistanceInLane() - distanceInLane - forwardVehicle->GetLength();

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
