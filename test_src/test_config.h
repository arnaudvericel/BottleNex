#include <cxxtest/TestSuite.h>
#include "../src/config.h"
#include "../src/constants.h"

class TestConfig : public CxxTest::TestSuite
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

    // Tests that every configuration field takes the correct value by default
    void TestDefault()
    {
        TS_ASSERT_EQUALS(testConfig->GetLanesData().size(), 0);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::FactorCFL], constants::sim::factorCFLDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::MaxTimeMin], constants::sim::maxTimeMinDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarAcceleration], constants::car::accelerationDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarAccelerationDistanceFactor], constants::car::accelDistanceFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarBrakingDistanceFactor], constants::car::brakingDistanceFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarDeceleration], constants::car::decelerationDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarLength], constants::car::lengthDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarSafeDistanceToEnterLaneFactor], constants::car::safeDistanceToEnterLaneFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarStartVelocityFactor], constants::car::startVelocityFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::IntSettings::NbDumps], constants::sim::nbDumpsDefault);
    }

    // Tests the Set method that permits fields configuration on the fly
    void TestSet()
    {
        for (Config::FloatSettings setting=Config::FloatSettings::MaxTimeMin; setting!= Config::FloatSettings::CarSafeDistanceToEnterLaneFactor; ++setting)
        {
            testConfig->Set(setting, (int)setting);
            TS_ASSERT_EQUALS((*testConfig)[setting], (int)setting);
        }

        for (Config::IntSettings setting=Config::IntSettings::NbDumps; setting!= Config::IntSettings::NbDumps; ++setting)
        {
            testConfig->Set(setting, (int)setting);
            TS_ASSERT_EQUALS((*testConfig)[setting], (int)setting);
        }

    }

    // Tests that the Config object resets correctly, i.e. values go back to default
    void TestReset()
    {
        float carLenghtDef = (*testConfig)[Config::FloatSettings::CarLength];
        float maxTimeDef = (*testConfig)[Config::FloatSettings::MaxTimeMin];
        int nbDumpsDef = (*testConfig)[Config::IntSettings::NbDumps];

        testConfig->Set(Config::FloatSettings::CarLength, 354);
        testConfig->Set(Config::FloatSettings::MaxTimeMin, 4756);
        testConfig->Set(Config::IntSettings::NbDumps, 45000);

        // test the changes applied to the config object
        TS_ASSERT_DIFFERS((*testConfig)[Config::FloatSettings::CarLength], carLenghtDef);
        TS_ASSERT_DIFFERS((*testConfig)[Config::FloatSettings::MaxTimeMin], maxTimeDef);
        TS_ASSERT_DIFFERS((*testConfig)[Config::IntSettings::NbDumps], nbDumpsDef);

        // resets the config object
        delete testConfig;
        testConfig = Config::GetConfig();

        // test back the default behaviour
        TestDefault();
    }

    // Tests configuration loading from input files
    void TestLoad()
    {
        // CASE 1
        Config::LoadConfig("../test_src/test_configs/test_config_case1_OK.cfg", false);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::MaxTimeMin], 5);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::FactorCFL], 2);
        TS_ASSERT_EQUALS((*testConfig)[Config::IntSettings::NbDumps], 500);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::FactoryFactorMin], 60);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::FactoryFactorMax], 140);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarLength], 7);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarAcceleration], 2);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarDeceleration], 8);
        std::vector<LaneData> dataLanes = testConfig->GetLanesData();
        TS_ASSERT_EQUALS(dataLanes.size(), 1);
        TS_ASSERT_EQUALS(dataLanes[0].length, 5000);
        TS_ASSERT_EQUALS(dataLanes[0].limitVelocity, 130);
        TS_ASSERT_EQUALS(dataLanes[0].vehiclesPerMinute, 50);
        TS_ASSERT_EQUALS(dataLanes[0].hasInputLane, false);
        delete testConfig;

        // CASE 2
        testConfig = Config::GetConfig();
        Config::LoadConfig("../test_src/test_configs/test_config_case2_OK.cfg", false);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarLength], 5);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarAcceleration], 5);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarDeceleration], 15);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarBrakingDistanceFactor], 3);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarAccelerationDistanceFactor], 8);
        TS_ASSERT_DELTA((*testConfig)[Config::FloatSettings::CarStartVelocityFactor], 0.2, 0.001);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarSafeDistanceToEnterLaneFactor], 3);
        dataLanes = testConfig->GetLanesData();
        TS_ASSERT_EQUALS(dataLanes.size(), 1);
        TS_ASSERT_EQUALS(dataLanes[0].length, 5000);
        TS_ASSERT_EQUALS(dataLanes[0].limitVelocity, 130);
        TS_ASSERT_EQUALS(dataLanes[0].vehiclesPerMinute, 40);
        TS_ASSERT_EQUALS(dataLanes[0].hasInputLane, true);
        TS_ASSERT_EQUALS(dataLanes[0].inputLaneJunctionDistance, 1500);
        TS_ASSERT_EQUALS(dataLanes[0].inputLaneLength, 1000);
        TS_ASSERT_EQUALS(dataLanes[0].inputLaneLimitVelocity, 80);
        TS_ASSERT_EQUALS(dataLanes[0].inputLaneVehiclesPerMinute, 30);
        delete testConfig;

        // CASE 3 : error on the sim data
        testConfig = Config::GetConfig();
        TS_ASSERT_THROWS(Config::LoadConfig("../test_src/test_configs/test_config_error_sim.cfg", false), std::logic_error);

        // CASE 4 : error on the car data
        testConfig = Config::GetConfig();
        TS_ASSERT_THROWS(Config::LoadConfig("../test_src/test_configs/test_config_error_car.cfg", false), std::logic_error);

        // CASE 5 : error on the factory data
        testConfig = Config::GetConfig();
        TS_ASSERT_THROWS(Config::LoadConfig("../test_src/test_configs/test_config_error_factory.cfg", false), std::logic_error);

        // CASE 6 : error on the lane data
        testConfig = Config::GetConfig();
        TS_ASSERT_THROWS(Config::LoadConfig("../test_src/test_configs/test_config_error_lane.cfg", false), std::logic_error);
    }
};