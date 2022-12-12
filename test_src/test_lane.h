#include <cxxtest/TestSuite.h>

#include "../src/config.h"
#include "../src/constants.h"
#include "../src/lane.h"
#include "../src/car.h"

class TestLane : public CxxTest::TestSuite
{
public:
    Config* testConfig;
    Lane* testLane;

    void setUp()
    {
        testLane = new Lane();
        testConfig = Config::GetConfig();
    }

    void tearDown()
    {
        delete testLane;
        delete testConfig;
    }

    // Tests the default behaviour of the Lane object
    void TestDefault()
    {
        TS_ASSERT_EQUALS(testLane->GetLength(), constants::lane::lengthDefault);
        TS_ASSERT_DELTA(testLane->GetLimitVelocity(), constants::lane::limitVelocityDefault / 3.6, 0.001);
        TS_ASSERT_EQUALS(testLane->GetVehiclesPerMinute(), constants::lane::vehiclesPerMinuteDefault);
        TS_ASSERT_EQUALS(testLane->GetFreeSpaceOnLane(), testLane->GetLength());
        TS_ASSERT(!testLane->HasParentLane());
        TS_ASSERT_EQUALS(testLane->GetNbVehiclesOnLane(), 0);
        TS_ASSERT_EQUALS(testLane->GetJunctionPoint(), 0);
    }

    // Tests the default behaviour of the Input Lane object
    void TestInputDefault()
    {
        float junPoint = testLane->GetLength() / 2.;
        Lane* testInputLane = new InputLane(testLane, junPoint, testLane->GetLength(), testLane->GetLimitVelocity()*3.6, testLane->GetVehiclesPerMinute());

        TS_ASSERT_EQUALS(testInputLane->GetLength(), testLane->GetLength());
        TS_ASSERT_EQUALS(testInputLane->GetLimitVelocity(), testLane->GetLimitVelocity());
        TS_ASSERT_EQUALS(testInputLane->GetVehiclesPerMinute(), testLane->GetVehiclesPerMinute());
        TS_ASSERT_EQUALS(testInputLane->GetFreeSpaceOnLane(), testLane->GetLength());
        TS_ASSERT_EQUALS(testInputLane->GetJunctionPoint(), testLane->GetLength() / 2.);
        TS_ASSERT(testInputLane->HasParentLane());
        TS_ASSERT_EQUALS(testInputLane->GetNbVehiclesOnLane(), 0);

        delete testInputLane;
    }

    // Tests the deletion of a vehicle on lane
    void TestDeleteVehicle()
    {
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
            delete vehicle;
        }
    }

    // Tests that the vehicles move correctly on lane
    void TestMoveVehicle()
    {
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

    // Tests that vehicles on an input lane transfers correctly to their parent lane
    void TestTransfertVehicleToParent()
    {
        float junPoint = testLane->GetLength() / 2.;
        Lane* testInputLane = new InputLane(testLane, junPoint, testLane->GetLength(), testLane->GetLimitVelocity()*3.6, testLane->GetVehiclesPerMinute());
        Vehicle* testCar = new Car(testInputLane, 1.);

        testInputLane->InsertVehicle(testCar);

        TS_ASSERT(testInputLane->IsOnLane(testCar));
        TS_ASSERT(!testLane->IsOnLane(testCar));
        TS_ASSERT_EQUALS(testLane->GetNbVehiclesOnLane(), 0);
        TS_ASSERT_EQUALS(testInputLane->GetNbVehiclesOnLane(), 1);
        
        testInputLane->TransferVehicleToParentLane(testCar);

        TS_ASSERT(!testInputLane->IsOnLane(testCar));
        TS_ASSERT(testLane->IsOnLane(testCar));
        TS_ASSERT_EQUALS(testLane->GetNbVehiclesOnLane(), 1);
        TS_ASSERT_EQUALS(testInputLane->GetNbVehiclesOnLane(), 0);

        testCar->SetDistanceInlane(testLane->GetLength() * 0.75);

        Vehicle* anotherTestCar = new Car(testInputLane, 1.);
        testInputLane->InsertVehicle(anotherTestCar);

        testInputLane->TransferVehicleToParentLane(anotherTestCar);

        TS_ASSERT_EQUALS(testInputLane->GetNbVehiclesOnLane(), 0);
        TS_ASSERT_EQUALS(testLane->GetNbVehiclesOnLane(), 2);
        TS_ASSERT(testLane->IsOnLane(anotherTestCar));
        TS_ASSERT_EQUALS(testLane->GetVehiclesOnLane()[0], testCar);
        TS_ASSERT_EQUALS(testLane->GetVehiclesOnLane()[1], anotherTestCar);
        TS_ASSERT_LESS_THAN(anotherTestCar->GetDistanceInLane(), testCar->GetDistanceInLane());

        delete testInputLane;
    }
};