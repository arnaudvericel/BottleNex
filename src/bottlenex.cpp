#include <iostream>

#include "road.h"
#include "vehicle_factory.h"
#include "config.h"

int main(int argc, char** argv)
{
    /* Run configuration */
    Config* myConfig = Config::GetConfig();

    myConfig->AddLane(LaneData());
    myConfig->AddLane(LaneData(4000, 110, 30, true, 1000, 1500, 90, 30));
    myConfig->Set(Config::FloatSettings::MaxTimeMin, 5);

    myConfig->PrintConfig();

    /* Instanciation of the Road object with its own vehicle factory */
    VehicleFactory* factory = new VehicleFactory();
    Road* road = new Road(factory);

    /* Road evolution */
    road->Evolve();

    /* End of the run */
    delete road;
    delete myConfig;
    delete factory;

    return 0;
}