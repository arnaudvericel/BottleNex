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
    std::vector<int> spawnStep;
    std::vector<Lane*> lanes;
    VehicleFactory* vehicleFactory;

    bool CanSpawnVehicle(const int, Lane*);
    void SpawnVehicles();
    bool IsDumpTimeStep() const;

public:
    Road(VehicleFactory*);
    ~Road();

    void Evolve(bool displayLoadingBar=true);
    //
    std::vector<Lane*> GetLanes() const;
    int GetNbLanes() const;
    float GetDeltaTime() const;
    float GetMaxTime() const;
    std::vector<int> GetSpawnStep() const;
    float GetCurrentTime() const;
};

#endif