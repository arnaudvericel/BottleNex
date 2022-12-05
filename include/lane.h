#ifndef LANE_H
#define LANE_H

#include <vector>

#include "writer.h"

class Vehicle;

class Lane
{
public:
    static int counter;

private:
    float maxAllowedSpeed;
    float length;
    int id;
    Writer writer = Writer();

    std::vector<Vehicle*> vehicles;

private:
    int FindInsertIndex(const Vehicle*, float);
    int FindVehicleIndex(const Vehicle*);
    std::vector<Vehicle*>::iterator FindVehicleIterIndex(const Vehicle*);
    void UpdateVehiclesLinklist();

public:
    Lane();
    Lane(float, float);
    ~Lane();

    void RemoveVehicle(Vehicle*);
    void InsertVehicle(Vehicle*);
    void InsertVehicle(Vehicle*, const float);
    void WriteStep(const float);

    std::vector<Vehicle*> GetVehiclesOnLane() const;
    int GetNbVehiclesOnLane() const;
    float GetMaxAllowedSpeed() const;
    float GetLength() const;
    int GetId() const;
    float GetFreeSpaceOnLane() const;
};

#endif