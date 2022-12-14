#include <iostream>
#include <cxxtest/TestSuite.h>
#include <utility>
#include <vector>

#include "../src/config.h"
#include "../src/vehicle_factory.h"
#include "../src/vehicle.h"
#include "../src/lane.h"

typedef std::pair<int,int> initFactors;

class TestVehicleFactory : public CxxTest::TestSuite
{
public:
    Config* testConfig;
    VehicleFactory* testFactory;
    std::vector<initFactors> testFactors;

    void setUp()
    {
        testConfig = Config::GetConfig();
    }

    void tearDown()
    {
        delete testConfig;
    }

    void doBuildTest(int factorMin, int factorMax)
    {
        testFactory = new VehicleFactory(factorMin, factorMax);
        Lane* testLane = new Lane();

        int nbVehiclesToSpawn = 300;
        float epsilon = 0.01;

        for (int i=0; i<nbVehiclesToSpawn; i++)
        {
            Vehicle* spawnedVehicle = testFactory->Build(testLane, VehicleType::Car);
            float vehicleInitVelocity = spawnedVehicle->GetCurrentVelocity();
            float vehicleStandardInitVelocity = (*testConfig)[Config::FloatSettings::CarStartVelocityFactor] * testLane->GetLimitVelocity();

            TS_ASSERT_LESS_THAN_EQUALS(vehicleInitVelocity, factorMax / 100. * vehicleStandardInitVelocity + epsilon);
            TS_ASSERT_LESS_THAN_EQUALS(factorMin / 100. * vehicleStandardInitVelocity - epsilon, vehicleInitVelocity);

            delete spawnedVehicle;
        }

        delete testFactory;
        delete testLane;
    }

    // Testing default constructor
    void TestDefault()
    {
        testFactory = new VehicleFactory();

        TS_ASSERT_EQUALS(testFactory->GetInitVelocityFactorMin(), (*testConfig)[Config::FloatSettings::FactoryFactorMin]);
        TS_ASSERT_EQUALS(testFactory->GetInitVelocityFactoryMax(), (*testConfig)[Config::FloatSettings::FactoryFactorMax]);

        delete testFactory;
    }

    // Testing the Build method on different factories
    void TestBuild()
    {
        // testing different pair of factory values
        testFactors.push_back(initFactors(75, 125));
        testFactors.push_back(initFactors(50, 150));
        testFactors.push_back(initFactors(25, 200));
        testFactors.push_back(initFactors(1, 100));

        for (std::vector<initFactors>::iterator factors_iter = testFactors.begin(); factors_iter != testFactors.end(); factors_iter++)
        {
            doBuildTest(factors_iter->first, factors_iter->second);
        }
    }
};