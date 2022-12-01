#include "../include/road.h"
#include "../include/lane.h"

Road::Road()
{
    // TODO
}

Road::Road(int nbLanes)
{
    for (int i = 0; i<nbLanes; i++)
    {
        lanes.push_back(new Lane());
    }
}

vector<Lane*> Road::GetLanes() const 
{ 
    return lanes; 
}