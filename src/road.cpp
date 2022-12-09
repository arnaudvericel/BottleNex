#include <iostream>
#include "time.h"

#include "road.h"
#include "lane.h"
#include "car.h" // fixme : vehicle factory
#include "config.h"

Road::Road(int nbLanes)
{
    Config* config = Config::GetConfig();
    srand(time(NULL));

    for (int i = 0; i<nbLanes; i++)
    {
        lanes.push_back(new Lane());
    }

    currentTime = 0.;
    maxTime = (*config)[Config::FloatSettings::MaxTimeMin] * 60;
    deltaTime = 3.6 * (*config)[Config::FloatSettings::CondCFL] * (*config)[Config::FloatSettings::CarLength] / (*config)[Config::FloatSettings::LaneLimitVelocity];
    spawnStep = (int)(60. / ((*config)[Config::FloatSettings::VehiclesPerMinute] * deltaTime));
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
    Config* config = Config::GetConfig();
    int step = (int) (currentTime / deltaTime);
    return (step % spawnStep == 0) && (lane->GetFreeSpaceOnLane() > (*config)[Config::FloatSettings::CarSafeDistanceToEnterLaneFactor] * (*config)[Config::FloatSettings::CarLength]);
}

void Road::SpawnVehicles()
{
    for (Lane* lane : lanes)
    {
        if (lane != nullptr && CanSpawnVehicle(lane))
        {
            float velocityMultiplier = (float)((rand() % 50 + 75) / 100.);
            lane->InsertVehicle(new Car(velocityMultiplier));
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
    int nbDumps = (*Config::GetConfig())[Config::IntSettings::NbDumps];
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