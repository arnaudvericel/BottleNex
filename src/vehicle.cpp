#include <iostream>

#include "vehicle.h"
#include "lane.h"

int Vehicle::nbActiveVehicles = 0;
int Vehicle::counter = 0;

Vehicle::~Vehicle()
{
    nbActiveVehicles--;
}

Vehicle::Vehicle()
{
    id = ++counter;
    nbActiveVehicles++;
    //
    length = 0;
    maxVelocity = 0;
    targetVelocity = 0;
    currentVelocity = 0;
    acceleration = 0;
    deceleration = 0;
    motionState = Motion::Accelerating;
    distanceInLane = 0;
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
    maxVelocity = lane->GetMaxAllowedSpeed();
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

void Vehicle::UpdateMotionState()
{
    if (currentVelocity > targetVelocity)
    {
        motionState = Motion::Braking;
    }
    else if (currentVelocity == targetVelocity)
    {
        motionState = Motion::Cruising;
    }
    else
    {
        motionState = Motion::Accelerating;
    }
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

        if (lane->HasParentLane())
        {   
            lane->TransferVehicleToParentLane(this);
        }
        else
        {
            lane->RemoveVehicle(this);
            delete this;
        }
    }

}