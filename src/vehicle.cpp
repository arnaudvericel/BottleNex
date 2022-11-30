#include <iostream>
#include "../include/vehicle.h"
#include "../include/lane.h"

Vehicle::Vehicle()
{
    // todo
}

Vehicle::Vehicle(float len, float maxspeed, float maxaccel) : length(len), maxSpeed(maxspeed), maxAcceleration(maxaccel) {}

float Vehicle::GetLength() const { return length; }

float Vehicle::GetMaxSpeed() const { return maxSpeed; }

float Vehicle::GetMaxAcceleration() const { return maxAcceleration; }

void Vehicle::Move() { cout << "I am moving virtually" << endl; }

Lane* Vehicle::GetLane() const { return lane; }

int Vehicle::GetPositionInLane() const { return positionInLane; }