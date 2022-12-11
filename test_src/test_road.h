#include <iostream>
#include <cxxtest/TestSuite.h>

#include "../src/road.h"
#include "../src/lane.h"
#include "../src/config.h"
#include "../src/constants.h"
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
        testRoad = new Road(testFactory);

        TS_ASSERT_EQUALS(testRoad->GetNbLanes(), 0);
        TS_ASSERT_EQUALS(testRoad->GetCurrentTime(), 0);
        TS_ASSERT_EQUALS(testRoad->GetDeltaTime(), constants::sim::deltaTimeDefault);
        TS_ASSERT_EQUALS(testRoad->GetMaxTime(), (*testConfig)[Config::FloatSettings::MaxTimeMin] * 60);
        TS_ASSERT_EQUALS(testRoad->GetSpawnStep().size(), 0);

        delete testRoad;
    }

    // Tests that the Road state is consistent after a call to the Evolve method, without input lane
    void TestEvolveNoInput()
    {
        float maxTimeMin = 2;
        float distanceToNextvehicle = 0;
        int prevVehicleCounter = Vehicle::counter;

        testConfig->Set(Config::FloatSettings::MaxTimeMin, maxTimeMin);
        testConfig->AddLane(LaneData());

        testRoad = new Road(testFactory);
        testRoad->Evolve(false);

        TS_ASSERT_DELTA(testRoad->GetCurrentTime(), testRoad->GetMaxTime(), testRoad->GetDeltaTime());
        TS_ASSERT_DELTA(Vehicle::counter - prevVehicleCounter, maxTimeMin*constants::lane::vehiclesPerMinuteDefault, 1);
        TS_ASSERT_EQUALS(testRoad->GetNbLanes(), 1);

        for (Lane* lane : testRoad->GetLanes())
        {
            for (Vehicle* vehicle : lane->GetVehiclesOnLane())
            {
                if (vehicle->GetForwardVehicle() != nullptr)
                {
                    distanceToNextvehicle = vehicle->GetForwardVehicle()->GetDistanceInLane() - vehicle->GetDistanceInLane();
                    TS_ASSERT_LESS_THAN(0, distanceToNextvehicle);
                }
            }
        }

        delete testRoad;
    }

    // Tests that the Road state is consistent after a call to the Evolve method, with input lane
    void TestEvolveWithInput()
    {
        float maxTimeMin = 5;
        float distanceToNextvehicle = 0;
        int prevVehicleCounter = Vehicle::counter;

        testConfig->Set(Config::FloatSettings::MaxTimeMin, maxTimeMin);
        testConfig->AddLane(LaneData(true));

        testRoad = new Road(testFactory);
        testRoad->Evolve(false);

        TS_ASSERT_DELTA(testRoad->GetCurrentTime(), testRoad->GetMaxTime(), testRoad->GetDeltaTime());
        TS_ASSERT_DELTA(Vehicle::counter - prevVehicleCounter, maxTimeMin*constants::lane::vehiclesPerMinuteDefault*2, 1);
        TS_ASSERT_EQUALS(testRoad->GetNbLanes(), 2);

        for (Lane* lane : testRoad->GetLanes())
        {
            for (Vehicle* vehicle : lane->GetVehiclesOnLane())
            {
                if (vehicle->GetForwardVehicle() != nullptr)
                {
                    distanceToNextvehicle = vehicle->GetForwardVehicle()->GetDistanceInLane() - vehicle->GetDistanceInLane();
                    TS_ASSERT_LESS_THAN(0, distanceToNextvehicle); // FIXME
                }
            }
        }

        delete testRoad;
    }
};