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
    float limitVelocity;
    float length;
    float vehiclesPerMinute;
    int id;
    Writer writer = Writer();
    std::vector<Vehicle*> vehicles;
    Lane* parentLane;
    float junctionPoint;

    std::vector<Vehicle*>::iterator FindInsertIterIndex(float);
    int FindVehicleIndex(const Vehicle*);
    std::vector<Vehicle*>::iterator FindVehicleIterIndex(const Vehicle*);
    void UpdateVehiclesLinklist();

public:
    Lane();
    Lane(float len, float maxV, float vPerMin);
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
    bool IsOnLane(Vehicle*) const;
    int GetNbVehiclesOnLane() const;
    float GetLimitVelocity() const;
    float GetLength() const;
    float GetVehiclesPerMinute() const;
    float GetJunctionPoint() const;
    int GetId() const;
    float GetFreeSpaceOnLane() const;
};

class InputLane : public Lane
{
public:
    InputLane(Lane* parent, float junPoint, float lengthm, float maxspeed, float vPerMin);
    ~InputLane() = default;
};

#endif