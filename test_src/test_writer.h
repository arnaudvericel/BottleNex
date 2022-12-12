#include <iostream>
#include <cxxtest/TestSuite.h>

#include "../src/writer.h"
#include "../src/lane.h"
#include "../src/car.h"

class TestWriter : public CxxTest::TestSuite
{
public:
    Lane* testLane;
    Writer* testWriter;

    void setUp()
    {
        testLane = new Lane();
        testWriter = new Writer();
        testWriter->Init(testLane);
    }

    void tearDown()
    {
        delete testLane;
        delete testWriter;
    }

    // Tests the initialization of a Writer object
    void TestInit()
    {
        TS_ASSERT_EQUALS(testWriter->GetLane(), testLane);
        TS_ASSERT_DIFFERS(testWriter->GetFileName(), "");
    }

    void TestGetStats()
    {
        float epsilon = 0.01;
        //
        Vehicle* carOne = new Car(testLane, 0.8);
        Vehicle* carTwo = new Car(testLane, 0.9);
        //
        testLane->InsertVehicle(carOne);
        carOne->SetDistanceInlane(testLane->GetLength() * 0.75);
        testLane->InsertVehicle(carTwo);
        carTwo->SetDistanceInlane(testLane->GetLength() * 0.25);
        
        float meanVelocityTheoric = (carOne->GetCurrentVelocity() + carTwo->GetCurrentVelocity()) / 2.;
        float meanDistanceTheoric = carOne->GetDistanceInLane() - carTwo->GetDistanceInLane();
        float meanDensityTheoric =  2 * 100 / testLane->GetLength();

        TS_ASSERT_DELTA(testWriter->GetMeanVelocity(), meanVelocityTheoric, epsilon);
        TS_ASSERT_DELTA(testWriter->GetMeanDistance(), meanDistanceTheoric, epsilon);
        TS_ASSERT_DELTA(testWriter->GetMeanDensity(), meanDensityTheoric, epsilon);
    }
};