#include <cxxtest/TestSuite.h>

#include "../src/config.h"
#include "../src/constants.h"
#include "../src/lane.h"
#include "../src/car.h"

class TestLane : public CxxTest::TestSuite
{
public:
    Config* testConfig;

    void setUp()
    {
        testConfig = Config::GetConfig();
    }

    void tearDown()
    {
        delete testConfig;
    }

    // Tests the default behaviour of the Lane object
    void TestDefault()
    {
        Lane* testLane = new Lane();

        TS_ASSERT_EQUALS(testLane->GetLength(), constants::lane::lengthDefault);
        TS_ASSERT_DELTA(testLane->GetLimitVelocity(), constants::lane::limitVelocityDefault / 3.6, 0.001);
        TS_ASSERT_EQUALS(testLane->GetVehiclesPerMinute(), constants::lane::vehiclesPerMinuteDefault);
        TS_ASSERT_EQUALS(testLane->GetFreeSpaceOnLane(), testLane->GetLength());
        TS_ASSERT(!testLane->HasParentLane());
        TS_ASSERT_EQUALS(testLane->GetNbVehiclesOnLane(), 0);
        TS_ASSERT_EQUALS(testLane->GetJunctionPoint(), 0);

        delete testLane;
    }

    // Tests the default behaviour of the Input Lane object
    void TestInputDefault()
    {
        Lane* testParentLane = new Lane();
        float junPoint = testParentLane->GetLength() / 2.;
        InputLane* testInputLane = new InputLane(testParentLane, junPoint, testParentLane->GetLength(), testParentLane->GetLimitVelocity()*3.6, testParentLane->GetVehiclesPerMinute());

        TS_ASSERT_EQUALS(testInputLane->GetLength(), testParentLane->GetLength());
        TS_ASSERT_EQUALS(testInputLane->GetLimitVelocity(), testParentLane->GetLimitVelocity());
        TS_ASSERT_EQUALS(testInputLane->GetVehiclesPerMinute(), testParentLane->GetVehiclesPerMinute());
        TS_ASSERT_EQUALS(testInputLane->GetFreeSpaceOnLane(), testInputLane->GetLength());
        TS_ASSERT_EQUALS(testInputLane->GetJunctionPoint(), testParentLane->GetLength() / 2.);
        TS_ASSERT(testInputLane->HasParentLane());
        TS_ASSERT_EQUALS(testInputLane->GetNbVehiclesOnLane(), 0);

        delete testInputLane;
        delete testParentLane;
    }

    // Tests the deletion of a vehicle on lane
    void TestDeleteVehicle()
    {
        Lane* testLane = new Lane();

        for (int i=0; i<10; i++)
        {
            Vehicle* newCar = new Car(testLane, 1);
            testLane->InsertVehicle(newCar);
            newCar->SetDistanceInlane(i * 50); // a vehicle each 50 meters
        }

        int counter = testLane->GetNbVehiclesOnLane();
        for (Vehicle* vehicle : testLane->GetVehiclesOnLane())
        {
            TS_ASSERT(testLane->IsOnLane(vehicle));
            testLane->RemoveVehicle(vehicle);
            counter--;
            TS_ASSERT(!testLane->IsOnLane(vehicle));
            TS_ASSERT_EQUALS(testLane->GetNbVehiclesOnLane(), counter);
        }

        delete testLane;
    }

    void TestMoveVehicle()
    {
        Lane* testLane = new Lane();
        Vehicle* testCar = new Car(testLane, 1);
        testLane->InsertVehicle(testCar);

        float prevDistanceInLane = testCar->GetDistanceInLane();

        for (int i = 0; i < 300; i++)
        {
            testLane->MoveVehicles(constants::sim::deltaTimeDefault);

            if (testCar != nullptr)
            {
                TS_ASSERT_LESS_THAN(prevDistanceInLane, testCar->GetDistanceInLane());
                prevDistanceInLane = testCar->GetDistanceInLane();
            }
        }
    }

    // TestInsertVehicle
    // TestTransfertVehicleToParent
};