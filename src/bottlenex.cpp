#include <iostream>
#include <string>

#include "road.h"
#include "vehicle_factory.h"
#include "config.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage : ./bottlenex <config_file>" << std::endl;
        return 0;
    }

    std::string configFile = argv[argc-1];

    /* Set and print configuration */
    Config* myConfig = Config::GetConfig();
    Config::LoadConfig(configFile);
    myConfig->PrintConfig();

    /* Instanciation of the Road object and its own vehicle factory */
    VehicleFactory* factory = new VehicleFactory();
    Road* road = new Road(factory);

    /* Launching the simulation */
    road->Evolve();

    /* End of the run */
    delete road;
    delete myConfig;
    delete factory;

    return 0;
}