#include <iostream>
#include "../include/vehicle.h"
#include "../include/lane.h"

int Vehicle::nbActiveVehicles = 0;
int Vehicle::counter = 0;

Vehicle::~Vehicle()
{
    nbActiveVehicles--;
}

Vehicle::Vehicle(float len, float maxspeed, float accel)
{
    // characteristics
    length = len;
    maxVelocity = maxspeed;
    acceleration = accel;
    id = ++counter;

    // dynamic state init
    motionState = Motion::Accelerating;
    distanceInLane = 0.;
    currentVelocity = 0.;
    nbActiveVehicles++;
}

float Vehicle::GetLength() const
{ 
    return length; 
}

float Vehicle::GetCurrentVelocity() const 
{ 
    return currentVelocity;
}

float Vehicle::GetMaxVelocity() const 
{ 
    return maxVelocity; 
}

float Vehicle::GetAcceleration() const 
{ 
    return acceleration;
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

    if (vehicle != nullptr && vehicle->GetBackwardVehicle() != this)
    {
        vehicle->SetBackwardVehicle(this);
    }
}

Vehicle* Vehicle::GetForwardVehicle() const
{
    return forwardVehicle;
}

int Vehicle::GetId() const
{
    return id;
}

void Vehicle::SetBackwardVehicle(Vehicle* vehicle)
{
    backwardVehicle = vehicle;

    if (vehicle != nullptr && vehicle->GetForwardVehicle() != this)
    {
        vehicle->SetForwardVehicle(this);
    }
}

Vehicle* Vehicle::GetBackwardVehicle() const
{
    return backwardVehicle;
}

Motion Vehicle::GetMotionState() const
{
    return motionState;
}

void Vehicle::UpdatePosition(const float deltaTime)
{
    distanceInLane += currentVelocity * deltaTime;
}

void Vehicle::Move(const float deltaTime)
{
    EvaluateMotionState(deltaTime);

    switch (motionState)
    {
    case Motion::Braking:
        Brake(deltaTime);
        break;
    
    case Motion::Cruising:
        Cruise(deltaTime);
        break;

    case Motion::Accelerating:
        Accelerate(deltaTime);
        break;
    
    default:
        break;
    }
    
    if (distanceInLane > lane->GetLength())
    {
        lane->RemoveVehicle(this);
    }
}