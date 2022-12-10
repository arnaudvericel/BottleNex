#include <iostream>

#include "enums.h"
#include "road.h"
#include "lane.h"
#include "config.h"
#include "vehicle_factory.h"

Road::Road(int nbLanes, VehicleFactory* factory)
{
    Config* config = Config::GetConfig();
    vehicleFactory = factory;

    for (int i = 0; i<nbLanes; i++)
    {
        lanes.push_back(new Lane());
    }

    currentTime = 0.;
    maxTime = (*config)[Config::FloatSettings::MaxTimeMin] * 60;
    deltaTime = 3.6 * (*config)[Config::FloatSettings::FactorCFL] * (*config)[Config::FloatSettings::CarLength] / (*config)[Config::FloatSettings::LaneLimitVelocity];
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
            Vehicle* newVehicle = vehicleFactory->Build(VehicleType::Car);
            lane->InsertVehicle(newVehicle);
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
            lane->MoveVehicles(deltaTime);

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

std::vector<Lane*> Road::GetLanes() const 
{ 
    return lanes; 
}

int Road::GetNbLanes() const
{
    return lanes.size();
}

float Road::GetDeltaTime() const
{
    return deltaTime;
}

float Road::GetMaxTime() const
{
    return maxTime;
}

int Road::GetSpawnStep() const
{
    return spawnStep;
}

float Road::GetCurrentTime() const
{
    return currentTime;
}