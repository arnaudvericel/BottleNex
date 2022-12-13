#include <iostream>

#include "utils.h"
#include "enums.h"
#include "road.h"
#include "lane.h"
#include "config.h"
#include "constants.h"
#include "vehicle_factory.h"

Road::Road(VehicleFactory* factory)
{
    Config* config = Config::GetConfig();
    vehicleFactory = factory;

    currentTime = 0.;
    maxTime = (*config)[Config::FloatSettings::MaxTimeMin] * 60;

    std::vector<LaneData> lanesData = config->GetLanesData();

    if (lanesData.size() > 0)
    {
        deltaTime = 3.6 * (*config)[Config::FloatSettings::FactorCFL] * (*config)[Config::FloatSettings::CarLength] / lanesData[0].limitVelocity;
        for (LaneData& lData : lanesData)
        {
            Lane* newLane = new Lane(lData.length, lData.limitVelocity, lData.vehiclesPerMinute);
            lanes.push_back(newLane);
            spawnStep.push_back((int)(60. / (lData.vehiclesPerMinute * deltaTime)));
            if (lData.hasInputLane)
            {
                lanes.push_back(new InputLane(newLane, lData.inputLaneJunctionDistance, lData.inputLaneLength, lData.inputLaneLimitVelocity, lData.inputLaneVehiclesPerMinute));
                spawnStep.push_back((int)(60. / (lData.inputLaneVehiclesPerMinute * deltaTime)));
            }
        }
    }
    else
    {
        // fixme : throw exception : no lanes to simulate ?
        deltaTime = constants::sim::deltaTimeDefault;
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

void Road::Evolve(bool displayLoadingBar)
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
        if (displayLoadingBar)
        {
            DisplayLoadingBar(currentTime / maxTime);
        }
    }
}

void Road::SpawnVehicles()
{
    int index = 0;
    for (Lane* lane : lanes)
    {
        if (lane != nullptr && CanSpawnVehicle(index, lane))
        {
            Vehicle* newVehicle = vehicleFactory->Build(lane, VehicleType::Car);
            lane->InsertVehicle(newVehicle);
        }
        index++;
    }
}

bool Road::CanSpawnVehicle(const int laneIndex, Lane* lane)
{
    Config* config = Config::GetConfig();
    int step = (int) (currentTime / deltaTime);
    return (step % spawnStep[laneIndex] == 0) && (lane->GetFreeSpaceOnLane() > (*config)[Config::FloatSettings::CarSafeDistanceToEnterLaneFactor] * (*config)[Config::FloatSettings::CarLength]);
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

std::vector<int> Road::GetSpawnStep() const
{
    return spawnStep;
}

float Road::GetCurrentTime() const
{
    return currentTime;
}