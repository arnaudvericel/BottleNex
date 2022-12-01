#include <iostream>
#include "../include/vehicle.h"
#include "../include/lane.h"

Vehicle::Vehicle()
{
    motionState = Motion::Cruising;
    distanceInLane = 0.;
    // todo : current speed
}

Vehicle::Vehicle(float len, float maxspeed, float maxaccel) : length(len), maxSpeed(maxspeed), maxAcceleration(maxaccel) 
{
    Vehicle();
}

float Vehicle::GetLength() const
{ 
    return length; 
}

float Vehicle::GetCurrentSpeed() const 
{ 
    return currentSpeed;
}

float Vehicle::GetMaxSpeed() const 
{ 
    return maxSpeed; 
}

float Vehicle::GetMaxAcceleration() const 
{ 
    return maxAcceleration; 
}

void Vehicle::SetLane(Lane* newLane) 
{
    lane = newLane; 
}

Lane* Vehicle::GetLane() const 
{ 
    return lane; 
}

float Vehicle::GetDistanceInLane() const 
{ 
    return distanceInLane; 
}

void Vehicle::SetForwardVehicle(Vehicle* vehicle)
{
    forwardVehicle = vehicle;
}

Vehicle* Vehicle::GetForwardVehicle() const
{
    return forwardVehicle;
}

void Vehicle::Move(float deltaTime)
{
    switch (motionState)
    {
    case Motion::Stopped:
        break;

    case Motion::Braking:
        /* code */
        break;
    
    case Motion::Cruising:
        /* code */
        break;

    case Motion::Accelerating:
        /* code */
        break;
    
    default:
        break;
    }
    
    if (distanceInLane > lane->GetLength())
    {
        lane->RemoveVehicle(this);
    }
}