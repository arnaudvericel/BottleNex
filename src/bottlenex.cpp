#include <iostream>
#include <vector>
#include "../include/lane.h"
#include "../include/car.h"

using namespace std;

int main(int argc, char** argv)
{
    Lane lane_example = Lane(110., 3.);

    Vehicle* new_car = new Car();
    Vehicle* another_car = new Car();

    lane_example.InsertVehicle(new_car);
    lane_example.InsertVehicle(another_car);

    vector<Vehicle*> vehiclesOnLane = lane_example.GetVehiclesOnLane();

    for (Vehicle* vehicle : vehiclesOnLane)
    {
        vehicle->Move();
    }

    return 0;
}