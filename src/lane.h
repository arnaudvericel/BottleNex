#ifndef LANE_H
#define LANE_H

#include <vector>

#include "writer.h"

class Vehicle;

class Lane
{
public:
    static int counter;

protected:
    float maxAllowedSpeed;
    float length;
    int id;
    Writer writer = Writer();
    std::vector<Vehicle*> vehicles;
    Lane* parentLane;

    std::vector<Vehicle*>::iterator FindInsertIterIndex(const Vehicle*, float);
    int FindVehicleIndex(const Vehicle*);
    std::vector<Vehicle*>::iterator FindVehicleIterIndex(const Vehicle*);
    void UpdateVehiclesLinklist();

public:
    Lane();
    ~Lane();

    void MoveVehicles(const float&);
    void TransferVehicleToParentLane(Vehicle*);
    void RemoveVehicle(Vehicle*);
    void InsertVehicle(Vehicle*);
    void InsertVehicle(Vehicle*, std::vector<Vehicle*>::iterator);
    void WriteStep(const float);

    bool HasParentLane() const;
    Lane* GetParentLane() const;

    std::vector<Vehicle*> GetVehiclesOnLane() const;
    int GetNbVehiclesOnLane() const;
    float GetMaxAllowedSpeed() const;
    float GetLength() const;
    int GetId() const;
    float GetFreeSpaceOnLane() const;
};

class InputLane : public Lane
{
public:
    InputLane(Lane*);
    InputLane(Lane*, float, float);
    ~InputLane() = default;
};

#endif