#include "config.h"
#include "constants.h"

#include <iostream>
#include <fstream>
#include <iomanip>

Config* Config::instance = nullptr;

Config::Config()
{
    InitSettings();
}

Config::~Config()
{
    instance = nullptr;
}

float& Config::operator[](const FloatSettings& settingName)
{
    return floatSettingsMap[settingName];
}

int& Config::operator[](const IntSettings& settingName)
{
    return intSettingsMap[settingName];
}

Config* Config::GetConfig()
{
    if (instance == nullptr)
    {
        instance = new Config();
    }
    return instance;
}

void Config::LoadConfig(std::string fileName)
{
    // todo : load fileName file to Config
}

void Config::Set(const IntSettings& settingName, const int& value)
{
    intSettingsMap[settingName] = value;
}

void Config::Set(const FloatSettings& settingName, const float& value)
{
    floatSettingsMap[settingName] = value;
}

void Config::InitSettings()
{
    // float settings
    Set(FloatSettings::MaxTimeMin, constants::sim::maxTimeMinDefault);
    Set(FloatSettings::FactorCFL, constants::sim::factorCFLDefault);
    Set(FloatSettings::LaneLimitVelocity, constants::lane::limitVelocityDefault);
    Set(FloatSettings::LaneLength, constants::lane::lengthDefault);
    Set(FloatSettings::CarMaxVelocity, constants::car::maxVelocityDefault);
    Set(FloatSettings::CarLength, constants::car::lengthDefault);
    Set(FloatSettings::CarAcceleration, constants::car::accelerationDefault);
    Set(FloatSettings::CarDeceleration, constants::car::decelerationDefault);
    Set(FloatSettings::VehiclesPerMinute, constants::lane::vehiclesPerMinuteDefault);
    Set(FloatSettings::CarBrakingDistanceFactor, constants::car::brakingDistanceFactorDefault);
    Set(FloatSettings::CarAccelerationDistanceFactor, constants::car::accelDistanceFactorDefault);
    Set(FloatSettings::CarCruisingDistanceFactor, constants::car::cruiseDistanceFactorDefault);
    Set(FloatSettings::CarSafeDistanceToEnterLaneFactor, constants::car::safeDistanceToEnterLaneFactorDefault);
    Set(FloatSettings::CarStartVelocityFactor, constants::car::startVelocityFactorDefault);
    Set(FloatSettings::FactoryFactorMin, constants::vehicle::factoryFactorMinDefault);
    Set(FloatSettings::FactoryFactorMax, constants::vehicle::factoryFactorMaxDefault);
    // int settings
    Set(IntSettings::NbDumps, constants::sim::nbDumpsDefault);
}

void Config::PrintConfig()
{
    std::cout << "*********************" << std::endl;
    std::cout << "*** Configuration ***" << std::endl;
    std::cout << "*********************" << std::endl;
    std::cout << std::endl;
    std::string nameCol = "Name";
    std::string valCol = "Value";
    std::string unitCol = "Unit";

    int nameWidth = 35;
    int valWidth = 10;
    int unitWidth = 10;

    std::cout << std::left << std::setw(nameWidth) << nameCol  << " -> " << std::setw(valWidth) << valCol << std::setw(unitWidth) << unitCol << std::endl;
    for (int i=0; i<nameWidth + valWidth + unitWidth + 3; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (auto it = floatSettingsMap.begin(); it != floatSettingsMap.end(); it++)
    {
        std::cout << std::left << std::setw(nameWidth) << it->first  << " -> " << std::setw(valWidth) << it->second << std::setw(unitWidth) << ConfigFloatSettingsUnit[(int)it->first] << std::endl;
    }

    for (auto it = intSettingsMap.begin(); it != intSettingsMap.end(); it++)
    {
        std::cout << std::left << std::setw(nameWidth) << it->first  << " -> " << std::setw(valWidth) << it->second << std::setw(unitWidth) << ConfigIntSettingsUnit[(int)it->first]  << std::endl;
    }
}

std::ostream& operator<<(std::ostream& stream, const Config::FloatSettings& setting)
{
    return stream << ConfigFloatSettingsName[(int)setting];
}

std::ostream& operator<<(std::ostream& stream, const Config::IntSettings& setting)
{
    return stream << ConfigIntSettingsName[(int)setting];
}

Config::FloatSettings& operator++(Config::FloatSettings& elem)
{
    if (elem == Config::FloatSettings::CarSafeDistanceToEnterLaneFactor)
    {
        throw std::out_of_range("for Config::FloatSettings operator ++");
    }
    elem = Config::FloatSettings(static_cast<std::underlying_type<Config::FloatSettings>::type>(elem) + 1);
    return elem;
}

Config::IntSettings& operator++(Config::IntSettings& elem)
{
    if (elem == Config::IntSettings::NbDumps)
    {
        throw std::out_of_range("for Config::IntSettings operator ++");
    }
    elem = Config::IntSettings(static_cast<std::underlying_type<Config::IntSettings>::type>(elem) + 1);
    return elem;
}