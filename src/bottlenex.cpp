#include <iostream>

#include "road.h"
#include "car.h"
#include "config.h"

int main(int argc, char** argv)
{
    Config* myConfig = Config::GetConfig();
    myConfig->PrintConfig();

    Road* road = new Road(1);

    road->Evolve();

    delete road;
    delete myConfig;

    return 0;
}