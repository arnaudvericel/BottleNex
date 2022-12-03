#include <iostream>

#include "../include/road.h"
#include "../include/lane.h"
#include "../include/car.h"

Road::Road(int nbLanes)
{
    currentTime = 0.;
    deltaTime = 0.1;
    maxTime = 120.;

    for (int i = 0; i<nbLanes; i++)
    {
        lanes.push_back(new Lane());
    }
}

Road::~Road()
{
    for (Lane* lane : lanes)
    {
        delete lane;
    }
}

bool Road::CanSpawnVehicle(Lane* lane)
{
    // TODO : option to spawn different types of vehicles
    int nbVehiclesOnLane = lane->GetNbVehiclesOnLane();
    if (nbVehiclesOnLane != 0)
    {
        Vehicle* lastVehicleOnLane = lane->GetVehiclesOnLane()[nbVehiclesOnLane - 1];
        float safeDistanceToEnterLane = 10 * Car::MaxVelocity * deltaTime;
        return lastVehicleOnLane->GetDistanceInLane() > safeDistanceToEnterLane;
    }
    else
    {
        return true;
    }
}

void Road::SpawnVehicles()
{
    for (Lane* lane : lanes)
    {
        if (CanSpawnVehicle(lane))
        {
            lane->InsertVehicle(new Car());
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
    int nbDumps = 1000;
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