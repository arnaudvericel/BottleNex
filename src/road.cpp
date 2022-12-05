#include <iostream>
#include "time.h"

#include "../include/road.h"
#include "../include/lane.h"
#include "../include/car.h"
#include "../include/constants.h"

Road::Road(int nbLanes)
{
    srand(time(NULL));
    currentTime = 0.;
    deltaTime = constants::sim::deltaTime;
    maxTime = constants::sim::maxTime;
    spawnStep = (int)(60. / constants::sim::vehiclesPerMin);

    for (int i = 0; i<nbLanes; i++)
    {
        lanes.push_back(new Lane());
    }
}

Road::~Road()
{
    for (Lane* lane : lanes)
    {
        if (lane != nullptr)
        {
            delete lane;
        }
    }
}

bool Road::CanSpawnVehicle(Lane* lane)
{
    int step = (int) (currentTime / deltaTime);
    return (step % spawnStep == 0) && (lane->GetFreeSpaceOnLane() > constants::car::safeDistanceToEnterLaneFactor * Car::Length);
}

void Road::SpawnVehicles()
{
    for (Lane* lane : lanes)
    {
        if (lane != nullptr && CanSpawnVehicle(lane))
        {
            float multiplier = (float)((rand() % 50 + 75) / 100.);
            lane->InsertVehicle(new Car(multiplier));
        }
    }
}

void Road::Evolve()
{
    bool isDumpTimeStep = false;

    while (currentTime < maxTime)
    {
        currentTime += deltaTime;
        SpawnVehicles();

        isDumpTimeStep = IsDumpTimeStep();

        for (Lane* lane : lanes)
        {
            for (Vehicle* vehicle : lane->GetVehiclesOnLane())
            {
                vehicle->Move(deltaTime);
            }
            if (isDumpTimeStep)
            {
                lane->WriteStep(currentTime);
            }
        }
    }
}

bool Road::IsDumpTimeStep() const
{
    int nbDumps = constants::sim::nbDumps;
    int step = (int) (currentTime / deltaTime);
    int nbSteps = (int)(maxTime / deltaTime);
    int dumpStep = nbSteps / nbDumps;

    if (nbDumps >= nbSteps) { return true; }

    return (step % dumpStep == 0) ;
}

vector<Lane*> Road::GetLanes() const 
{ 
    return lanes; 
}