#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../include/road.h"
#include "../include/lane.h"

class TestRoad : public CxxTest::TestSuite
{
public:
    Road* road;
    const int nbLanes = 1;
    void setUp()
    {
        road = new Road(nbLanes);
    }
    void tearDown()
    {
        delete road;
    }
    // TODO : complete
    void TestRoadLen()
    {
        TS_ASSERT_EQUALS(road->GetLanes().size(), 2);
    }
};