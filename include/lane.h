#ifndef LANE_H
#define LANE_H

#include <vector>

class Vehicle;

using namespace std;

class Lane
{
private:
    float maxSpeed;
    float lengthKm;

    vector<Vehicle*> vehicles;

private:
    void RemoveVehicle(Vehicle*);

public:
    Lane();
    Lane(float, float);
    ~Lane() = default;

    void InsertVehicle(Vehicle*);
    void InsertVehicle(Vehicle*, const float);

    vector<Vehicle*> GetVehiclesOnLane() const;
    float GetMaxSpeed() const;
    float GetLengthKm() const;
};

#endif