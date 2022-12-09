#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

#include "lane.h"
#include "vehicle.h"
#include "utils.h"
#include "car.h"
#include "config.h"

int Lane::counter = 0;

Lane::Lane()
{
    Config* config = Config::GetConfig();
    parentLane = nullptr;
    maxAllowedSpeed = (*config)[Config::FloatSettings::LaneLimitVelocity] / 3.6;
    length = (*config)[Config::FloatSettings::LaneLength];
    id = ++counter;
    writer.Init(this);
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

void Lane::TransferVehicleToParentLane(Vehicle* vehicleToTransfer)
{
    if (parentLane != nullptr)
    {
        // inserting the vehicle to its destination lane
        std::vector<Vehicle*>::iterator vehicleInsertIterIndex = parentLane->FindInsertIterIndex(vehicleToTransfer, vehicleToTransfer->GetDistanceInLane()); // fixme : junction Distance
        parentLane->InsertVehicle(vehicleToTransfer, vehicleInsertIterIndex);

        // removing the vehicle from its current lane
        RemoveVehicle(vehicleToTransfer);

        // rebuilding the vehicle link list on all affected lanes
        UpdateVehiclesLinklist();
        parentLane->UpdateVehiclesLinklist();
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

std::vector<Vehicle*>::iterator Lane::FindInsertIterIndex(const Vehicle* otherVehicle, float crossingPosition)
{
    int insertIndex = 0; // we start the search at the very first vehicle on lane (with largest distance on lane)
    
    // treating particular cases : inserted vehicle becomes first or last vehicle on lane
    if (vehicles.size() > 0)
    {
        if (crossingPosition > vehicles[0]->GetDistanceInLane())
        {
            insertIndex = 0;
        }
        else if (crossingPosition < vehicles[vehicles.size() - 1]->GetDistanceInLane())
        {
            insertIndex = vehicles.size() - 1;
        }
    }

    // treating all other cases
    for (int i=0; i<vehicles.size()-1; i++)
    {
        if (vehicles[i]->GetDistanceInLane() > crossingPosition && vehicles[i+1]->GetDistanceInLane() < crossingPosition)
        {
            insertIndex = i;
        }
    }

    return vehicles.begin() + insertIndex;
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
    }
}

void Lane::InsertVehicle(Vehicle* newVehicle)
{
    vehicles.push_back(newVehicle);
    newVehicle->SetLane(this);

    UpdateVehiclesLinklist();
    
}

void Lane::InsertVehicle(Vehicle* newVehicle, std::vector<Vehicle*>::iterator insertIterIndex)
{
    // todo check
    this->vehicles.insert(insertIterIndex, newVehicle);
    newVehicle->SetLane(this);
    UpdateVehiclesLinklist();
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

float Lane::GetFreeSpaceOnLane() const
{
    if (vehicles.size() > 0)
    {
        Vehicle* lastVehicleOnLane = vehicles[vehicles.size() - 1];
        return lastVehicleOnLane->GetDistanceInLane() - lastVehicleOnLane->GetLength();
    }
    else
    {
        return length;
    }
}

void Lane::WriteStep(const float time)
{
    writer.WriteStep(time);
}

bool Lane::HasParentLane() const
{
    return parentLane != nullptr;
}

Lane* Lane::GetParentLane() const
{
    return parentLane;
}

InputLane::InputLane(Lane* parent)
{
    parentLane = parent;
    writer.Init(this);
}

InputLane::InputLane(Lane* parent, float maxspeed, float lengthm) : InputLane(parent)
{
    maxAllowedSpeed = maxspeed;
    length = lengthm;
}