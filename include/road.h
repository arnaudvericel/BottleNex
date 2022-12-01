#ifndef ROAD_H
#define ROAD_H

#include <vector>

using namespace std;

class Lane;

class Road
{
private:
    vector<Lane*> lanes;

public:
    Road();
    Road(int);
    ~Road() = default;

    vector<Lane*> GetLanes() const;
};

#endif