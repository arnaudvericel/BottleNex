#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

#include "../include/lane.h"
#include "../include/vehicle.h"
#include "../include/utils.h"
#include "../include/car.h"

int Lane::counter = 0;

Lane::Lane()
{
    maxAllowedSpeed = 130.;
    length = 2000.; // m
    id = ++counter;
    writer.Init(this);
}

Lane::Lane(float maxspeed, float lengthm) : Lane()
{
    maxAllowedSpeed = maxspeed;
    length = lengthm; 
}

Lane::~Lane()
{
    for (Vehicle* vehicle : vehicles)
    {
        if (vehicle != nullptr)
        {
            delete vehicle;
        }
    }
}

std::vector<Vehicle*> Lane::GetVehiclesOnLane() const 
{ 
    return vehicles;
}

int Lane::GetNbVehiclesOnLane() const
{
    return vehicles.size();
}

int Lane::FindInsertIndex(const Vehicle* otherVehicle, float crossingPosition)
{
    // TODO
    return 0;
}

int Lane::FindVehicleIndex(const Vehicle* vehicleToFind)
{
    for(std::vector<Vehicle*>::iterator it = begin(vehicles); it != end(vehicles); ++it)
    {
        if (*it == vehicleToFind)
        {
            return std::distance(vehicles.begin(), it);
        }
    }
}

std::vector<Vehicle*>::iterator Lane::FindVehicleIterIndex(const Vehicle* vehicleToFind)
{
    for(std::vector<Vehicle*>::iterator it = begin(vehicles); it != end(vehicles); ++it)
    {
        if (*it == vehicleToFind)
        {
            return it;
        }
    }
}

void Lane::RemoveVehicle(Vehicle* vehicle)
{
    if (vehicle != nullptr)
    {
        auto vehicleIterIndex = FindVehicleIterIndex(vehicle);
        this->vehicles.erase(vehicleIterIndex);

        Vehicle* backwardVehicle = vehicle->GetBackwardVehicle();
        if (backwardVehicle != nullptr)
        {
            backwardVehicle->SetForwardVehicle(nullptr);
        }

        Vehicle* forwardVehicle = vehicle->GetForwardVehicle();
        if (forwardVehicle != nullptr)
        {
            forwardVehicle->SetBackwardVehicle(nullptr);
        }

        delete vehicle;
    }
}

void Lane::InsertVehicle(Vehicle* newVehicle)
{
    vehicles.push_back(newVehicle);
    newVehicle->SetLane(this);

    UpdateVehiclesLinklist();
    
}

void Lane::InsertVehicle(Vehicle* newVehicle, const float position)
{
    // todo
}

void Lane::UpdateVehiclesLinklist()
{
    for (int i=0; i<vehicles.size(); i++)
    {
        if (i != 0)
        {
            vehicles[i]->SetForwardVehicle(vehicles[i-1]);
        }
        else
        {
            // first vehicle in lane does not have a forward vehicle
            vehicles[i]->SetForwardVehicle(nullptr);
        }
    }
}

float Lane::GetMaxAllowedSpeed() const 
{
    return maxAllowedSpeed;
}

float Lane::GetLength() const
{
    return length;
}

int Lane::GetId() const
{
    return id;
}

void Lane::WriteStep(const float time)
{
    writer.WriteStep(time);
}