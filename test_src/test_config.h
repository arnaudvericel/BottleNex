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
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CondCFL], constants::sim::factorCFLDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::LaneLength], constants::lane::lengthDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::LaneLimitVelocity], constants::lane::limitVelocityDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::MaxTimeMin], constants::sim::maxTimeMinDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::VehiclesPerMinute], constants::lane::vehiclesPerMinuteDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarAcceleration], constants::car::accelerationDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarAccelerationDistanceFactor], constants::car::accelDistanceFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarBrakingDistanceFactor], constants::car::brakingDistanceFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarCruisingDistanceFactor], constants::car::cruiseDistanceFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarDeceleration], constants::car::decelerationDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarLength], constants::car::lengthDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarMaxVelocity], constants::car::maxVelocityDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarSafeDistanceToEnterLaneFactor], constants::car::safeDistanceToEnterLaneFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::FloatSettings::CarStartVelocityFactor], constants::car::startVelocityFactorDefault);
        TS_ASSERT_EQUALS((*testConfig)[Config::IntSettings::NbDumps], constants::sim::nbDumpsDefault);
    }

    // Tests the Set method that permits fields configurationon the fly
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

    void TestLoad()
    {
        TS_SKIP("TODO");
    }
};