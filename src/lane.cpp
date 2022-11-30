#include "../include/lane.h"
#include "../include/vehicle.h"

using namespace std;


Lane::Lane()
{
    maxSpeed = 130.;
    lengthKm = 2.;
}

Lane::Lane(float maxspeed, float lengthkm) : maxSpeed(maxspeed), lengthKm(lengthkm) {}

vector<Vehicle*> Lane::GetVehiclesOnLane() const { return vehicles; }

void Lane::RemoveVehicle(Vehicle* vehicle)
{
    // todo
}

void Lane::InsertVehicle(Vehicle* newVehicle)
{
    this->vehicles.push_back(newVehicle);
}

void Lane::InsertVehicle(Vehicle* newVehicle, const float position)
{
    // todo
}

float Lane::GetMaxSpeed() const 
{
    return maxSpeed;
}

float Lane::GetLengthKm() const
{
    return lengthKm;
}