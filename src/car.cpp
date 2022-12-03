#include <iostream>
#include "../include/car.h"
#include "../include/enums.h"

int Car::nbActiveCars = 0;

Car::Car() : Vehicle(Length, MaxVelocity, Acceleration)
{
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
    if (currentVelocity < maxVelocity)
    {
        currentVelocity += acceleration * deltaTime;
        if (currentVelocity > maxVelocity)
        {
            currentVelocity = maxVelocity;
        }
    }
    UpdatePosition(deltaTime);
}

void Car::EvaluateMotionState(const float deltaTime)
{
    // todo : complete

    float accelereationDistance = 5. * currentVelocity * deltaTime;
    float cruisingDistance = 10. * maxVelocity * deltaTime;
    float distanceToNextVehicle = 0.;

    if (forwardVehicle != nullptr)
    {
        distanceToNextVehicle = forwardVehicle->GetDistanceInLane() - distanceInLane;
    }
    else
    {
        // the first vehicle on lane does not have a forward vehicle
        distanceToNextVehicle = cruisingDistance;
    }

    if (distanceToNextVehicle < accelereationDistance)
    {
        motionState = Motion::Braking;
    }
    else if (distanceToNextVehicle < cruisingDistance)
    {
        motionState = Motion::Accelerating;
    }
    else
    {
        if (currentVelocity == maxVelocity)
        {
            motionState = Motion::Cruising;
        }
        else
        {
            motionState = Motion::Accelerating;
        }
    }
}
