#ifndef ROAD_H
#define ROAD_H

#include <vector>

using namespace std;

class Lane;

class Road
{
private:
    float currentTime;
    float deltaTime;
    float maxTime;
    int spawnStep;
    vector<Lane*> lanes;

    bool CanSpawnVehicle(Lane*);
    void SpawnVehicles();
    bool IsDumpTimeStep() const;

public:
    Road(int);
    ~Road();

    void Evolve();
    vector<Lane*> GetLanes() const;
    int GetNbLanes() const;
    float GetDeltaTime() const;
    float GetMaxTime() const;
    int GetSpawnStep() const;
    float GetCurrentTime() const;
};

#endif