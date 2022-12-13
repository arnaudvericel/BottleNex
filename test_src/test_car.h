#include <cxxtest/TestSuite.h>
#include <iostream>

#include "../src/config.h"
#include "../src/constants.h"
#include "../src/vehicle.h"
#include "../src/car.h"
#include "../src/lane.h"

class TestCar : public CxxTest::TestSuite
{
public:
    Lane* testLane;
    Vehicle* testCar;
    Config* testConfig;

    void setUp()
    {
        testConfig = Config::GetConfig();
        testConfig->Set(Config::FloatSettings::CarStartVelocityFactor, 1.);
        testLane = new Lane();
        testCar = new Car(testLane, 1.);
        testLane->InsertVehicle(testCar);
    }

    void tearDown()
    {
        delete testConfig;
        delete testLane;
    }

    // Tests the car initialization
    void TestInit()
    {
        TS_ASSERT_EQUALS(testCar->GetMaxVelocity(), testLane->GetLimitVelocity());
        TS_ASSERT_EQUALS(testCar->GetLength(), (*testConfig)[Config::FloatSettings::CarLength]);
        TS_ASSERT_EQUALS(testCar->GetLane(), testLane);
        TS_ASSERT_EQUALS(testCar->GetId(), Car::counter);
        TS_ASSERT_EQUALS(testCar->GetAcceleration(), (*testConfig)[Config::FloatSettings::CarAcceleration]);
        TS_ASSERT_EQUALS(testCar->GetDeceleration(), (*testConfig)[Config::FloatSettings::CarDeceleration]);
        TS_ASSERT_EQUALS(testCar->GetMotionState(), constants::car::startMotion);
        TS_ASSERT_EQUALS(Car::nbActiveCars, 1);
        TS_ASSERT_EQUALS(testCar->GetForwardVehicle(), nullptr);
        TS_ASSERT_EQUALS(testCar->GetBackwardVehicle(), nullptr);
    }
    
    // Tests the car linklist to forward and backward vehicles
    void TestLinkList()
    {
        float laneLength = testLane->GetLength();
        testCar->SetDistanceInlane(laneLength * 0.5);

        Vehicle* backwardCar = new Car(testLane, 1.);
        testLane->InsertVehicle(backwardCar);
        backwardCar->SetDistanceInlane(laneLength * 0.2);

        TS_ASSERT_EQUALS(testCar->GetForwardVehicle(), nullptr);
        TS_ASSERT_EQUALS(testCar->GetBackwardVehicle(), backwardCar);
        TS_ASSERT_EQUALS(backwardCar->GetForwardVehicle(), testCar);

        Vehicle* forwardCar = new Car(testLane, 1.);
        auto insertIterIndex = testLane->FindInsertIterIndex(laneLength * 0.8);
        testLane->InsertVehicle(forwardCar, insertIterIndex);
        forwardCar->SetDistanceInlane(laneLength * 0.8);

        TS_ASSERT_EQUALS(testCar->GetForwardVehicle(), forwardCar);
        TS_ASSERT_EQUALS(testCar->GetBackwardVehicle(), backwardCar);
        TS_ASSERT_EQUALS(backwardCar->GetForwardVehicle(), testCar);
        TS_ASSERT_EQUALS(forwardCar->GetBackwardVehicle(), testCar);

        testLane->RemoveVehicle(backwardCar);
        delete backwardCar;

        TS_ASSERT_EQUALS(testCar->GetBackwardVehicle(), nullptr);
        TS_ASSERT_EQUALS(testCar->GetForwardVehicle(), forwardCar);

        testLane->RemoveVehicle(forwardCar);
        delete forwardCar;

        TS_ASSERT_EQUALS(testCar->GetBackwardVehicle(), nullptr);
        TS_ASSERT_EQUALS(testCar->GetForwardVehicle(), nullptr);
    }

    // Tests that the motion state of vehicles is correctly updated wrt distance between vehicles
    void TestMotionState()
    {
        float deltaTime = constants::sim::deltaTimeDefault;
        Vehicle* forwardCar = new Car(testLane, 1.);

        // Case 1 : test car cruising
        testCar->SetForwardVehicle(forwardCar);
        forwardCar->SetDistanceInlane(testLane->GetLength() * 0.5);
        testCar->SetDistanceInlane(forwardCar->GetDistanceInLane() - (*testConfig)[Config::FloatSettings::CarLength] - 20);

        testCar->Move(deltaTime);
        forwardCar->Move(deltaTime);
        TS_ASSERT_EQUALS(testCar->GetMotionState(), Motion::Cruising);
        TS_ASSERT_EQUALS(forwardCar->GetMotionState(), Motion::Cruising);

        // Case 2 : test car braking
        testCar->SetForwardVehicle(forwardCar);
        forwardCar->SetDistanceInlane(testLane->GetLength() * 0.5);
        testCar->SetDistanceInlane(forwardCar->GetDistanceInLane() - (*testConfig)[Config::FloatSettings::CarLength] - 1);

        testCar->Move(deltaTime);
        forwardCar->Move(deltaTime);
        TS_ASSERT_EQUALS(testCar->GetMotionState(), Motion::Braking);
        TS_ASSERT_EQUALS(forwardCar->GetMotionState(), Motion::Cruising);

        // Case 3 : test car accelerating
        testCar->SetForwardVehicle(forwardCar);
        forwardCar->SetDistanceInlane(testLane->GetLength() * 0.5);
        testCar->SetDistanceInlane(forwardCar->GetDistanceInLane() - (*testConfig)[Config::FloatSettings::CarLength] - 400);

        testCar->Move(deltaTime);
        forwardCar->Move(deltaTime);
        TS_ASSERT_EQUALS(testCar->GetMotionState(), Motion::Accelerating);
        TS_ASSERT_EQUALS(forwardCar->GetMotionState(), Motion::Cruising);

        delete forwardCar;
    }
};