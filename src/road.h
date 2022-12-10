#ifndef ROAD_H
#define ROAD_H

#include <vector>

class Lane;
class VehicleFactory;

class Road
{
private:
    float currentTime;
    float deltaTime;
    float maxTime;
    int spawnStep;
    std::vector<Lane*> lanes;
    VehicleFactory* vehicleFactory;

    bool CanSpawnVehicle(Lane*);
    void SpawnVehicles();
    bool IsDumpTimeStep() const;

public:
    Road(int, VehicleFactory*);
    ~Road();

    void Evolve();
    std::vector<Lane*> GetLanes() const;
    int GetNbLanes() const;
    float GetDeltaTime() const;
    float GetMaxTime() const;
    int GetSpawnStep() const;
    float GetCurrentTime() const;
};

#endif