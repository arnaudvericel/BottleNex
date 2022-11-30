#ifndef VEHICLE_H
#define VEHICLE_H

using namespace std;

class Lane;

class Vehicle
{
private:
    float length;
    float maxSpeed;
    float maxAcceleration; // km/h/s
    Lane* lane;
    int positionInLane;

public:
    Vehicle();
    Vehicle(float, float, float);
    ~Vehicle() = default;

    float GetLength() const;
    float GetMaxSpeed() const;
    float GetMaxAcceleration() const;

    virtual void Move() = 0;

    Lane* GetLane() const;
    int GetPositionInLane() const;
};

#endif