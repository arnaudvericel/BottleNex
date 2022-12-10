#ifndef VEHICLE_H
#define VEHICLE_H

#include "enums.h"

class Lane;

class Vehicle
{
public:
    static int nbActiveVehicles;
    static int counter;

protected:
    // characteristics
    int id;
    float length;
    float maxVelocity;
    float acceleration; // m/s/s
    float deceleration; // m/s/s

    // evolution-related
    float targetVelocity;
    float currentVelocity;
    float distanceInLane;

    Motion motionState;

    Lane* lane;
    Vehicle* forwardVehicle;
    Vehicle* backwardVehicle;

    // methods
    virtual void Brake(const float) = 0;
    virtual void Cruise(const float) = 0;
    virtual void Accelerate(const float) = 0;
    virtual void EvaluateMotionState(const float) = 0;

    void UpdatePosition(const float);
    void UpdateMotionState();

public:
    Vehicle();
    virtual ~Vehicle();

    float GetLength() const;
    float GetCurrentVelocity() const;
    float GetDistanceInLane() const;
    float GetMaxVelocity() const;
    float GetAcceleration() const;
    void SetForwardVehicle(Vehicle*);
    Vehicle* GetForwardVehicle() const;
    void SetBackwardVehicle(Vehicle*);
    Vehicle* GetBackwardVehicle() const;
    int GetId() const;
    Motion GetMotionState() const;
    void SetLane(Lane*);
    Lane* GetLane() const;

    void Move(const float);
};

#endif