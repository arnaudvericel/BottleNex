#ifndef VEHICLE_H
#define VEHICLE_H

using namespace std;

enum Motion
{
    Stopped = 0,
    Braking,
    Cruising,
    Accelerating
};

class Lane;

class Vehicle
{
public:
    static int nbActiveVehicles;

private:
    // characteristics
    float length;
    float maxSpeed;
    float maxAcceleration; // km/h/s

    // evolution-related
    float currentSpeed;
    float distanceInLane;

    Motion motionState;

    Lane* lane;
    Vehicle* forwardVehicle;

public:
    Vehicle();
    Vehicle(float, float, float);
    virtual ~Vehicle();

    float GetLength() const;
    float GetCurrentSpeed() const;
    float GetDistanceInLane() const;
    float GetMaxSpeed() const;
    float GetMaxAcceleration() const;

    virtual void Move(float);

    void SetLane(Lane*);
    Lane* GetLane() const;

    void SetForwardVehicle(Vehicle*);
    Vehicle* GetForwardVehicle() const;
};

#endif