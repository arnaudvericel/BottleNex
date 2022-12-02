#include "../include/lane.h"
#include "../include/vehicle.h"

Lane::Lane()
{
    maxAllowedSpeed = 130.;
    length = 2.;
}

Lane::Lane(float maxspeed, float lengthm) : maxAllowedSpeed(maxspeed), length(lengthm) 
{

}

std::vector<Vehicle*> Lane::GetVehiclesOnLane() const 
{ 
    return vehicles;
}

int Lane::FindInsertPosition(const Vehicle* otherVehicle, float crossingPosition)
{
    // TODO
    return 0;
}

std::vector<Vehicle*>::iterator Lane::FindVehicleIndex(const Vehicle* vehicleToFind)
{
    for(auto it = begin(vehicles); it != end(vehicles); ++it)
    {
        if (*it == vehicleToFind)
        {
            return it;
        }
    }
}

void Lane::RemoveVehicle(Vehicle* vehicle)
{
    std::vector<Vehicle*>::iterator vehicleIndex = FindVehicleIndex(vehicle);
    // todo : remove link to previous vehicle?
    this->vehicles.erase(vehicleIndex);
    delete vehicle;
}

void Lane::InsertVehicle(Vehicle* newVehicle)
{
    vehicles.push_back(newVehicle);
    newVehicle->SetLane(this);
    newVehicle->SetForwardVehicle(nullptr);

    LinkFollowingVehicle(newVehicle);
    
}

void Lane::InsertVehicle(Vehicle* newVehicle, const float position)
{
    // todo
}

void Lane::LinkFollowingVehicle(Vehicle* vehicle)
{
    std::vector<Vehicle*>::iterator posInLane = FindVehicleIndex(vehicle);
    int index = std::distance(vehicles.begin(), posInLane);

    if (index > 0)
    {
        vehicles[index - 1]->SetForwardVehicle(vehicle);
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