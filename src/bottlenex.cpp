#include <iostream>

#include "road.h"
#include "vehicle_factory.h"
#include "config.h"

int main(int argc, char** argv)
{
    Config* myConfig = Config::GetConfig();
    myConfig->PrintConfig();

    VehicleFactory* factory = new VehicleFactory();

    Road* road = new Road(1, factory);

    road->Evolve();

    delete road;
    delete myConfig;
    delete factory;

    return 0;
}