#ifndef LANE_H
#define LANE_H

#include <vector>

class Vehicle;

class Lane
{
private:
    float maxAllowedSpeed;
    float length;

    std::vector<Vehicle*> vehicles;

private:
    int FindInsertPosition(const Vehicle*, float);
    std::vector<Vehicle*>::iterator FindVehicleIndex(const Vehicle*);

public:
    Lane();
    Lane(float, float);
    ~Lane() = default;

    void RemoveVehicle(Vehicle*);
    void InsertVehicle(Vehicle*);
    void InsertVehicle(Vehicle*, const float);

    void LinkFollowingVehicle(Vehicle*);

    std::vector<Vehicle*> GetVehiclesOnLane() const;
    float GetMaxAllowedSpeed() const;
    float GetLength() const;
};

#endif