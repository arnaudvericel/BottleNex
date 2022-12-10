#include <iostream>
#include <cxxtest/TestSuite.h>

#include "../src/road.h"
#include "../src/lane.h"
#include "../src/config.h"
#include "../src/vehicle_factory.h"
#include "../src/vehicle.h"

class TestRoad : public CxxTest::TestSuite
{
public:
    Config* testConfig;
    Road* testRoad;
    VehicleFactory* testFactory;

    void setUp()
    {
        testFactory = new VehicleFactory();
        testConfig = Config::GetConfig();
    }

    void tearDown()
    {
        delete testFactory;
        delete testConfig;
    }

    // Tests the initialization of the Road object
    void TestInit()
    {
        int nbLanes = 3;
        testRoad = new Road(nbLanes, testFactory);

        float roadDeltaTime = testRoad->GetDeltaTime();
        int spawStepTheoric = (int)(60. / ((*testConfig)[Config::FloatSettings::VehiclesPerMinute] * roadDeltaTime));

        TS_ASSERT_EQUALS(testRoad->GetNbLanes(), nbLanes);
        TS_ASSERT(roadDeltaTime > 0);
        TS_ASSERT_EQUALS(testRoad->GetMaxTime(), (*testConfig)[Config::FloatSettings::MaxTimeMin] * 60);
        TS_ASSERT_DELTA(testRoad->GetSpawnStep(), spawStepTheoric, 1);

        delete testRoad;
    }

    // Tests that the Road state is consistent after a call to the Evolve method
    void TestEvolve()
    {
        float nbVehiclesPerMin = 10;
        float maxTimeMin = 2;
        float distanceToNextvehicle = 0;

        testConfig->Set(Config::FloatSettings::MaxTimeMin, maxTimeMin);
        testConfig->Set(Config::FloatSettings::VehiclesPerMinute, nbVehiclesPerMin);

        testRoad = new Road(1, testFactory);
        testRoad->Evolve();

        TS_ASSERT_DELTA(testRoad->GetCurrentTime(), testRoad->GetMaxTime(), testRoad->GetDeltaTime());
        TS_ASSERT_DELTA(Vehicle::counter, maxTimeMin*nbVehiclesPerMin, 1);

        for (Lane* lane : testRoad->GetLanes())
        {
            for (Vehicle* vehicle : lane->GetVehiclesOnLane())
            {
                if (vehicle->GetForwardVehicle() != nullptr)
                {
                    distanceToNextvehicle = vehicle->GetForwardVehicle()->GetDistanceInLane() - vehicle->GetDistanceInLane();
                    TS_ASSERT(distanceToNextvehicle > 0);
                }
            }
        }

        delete testRoad;
    }
};