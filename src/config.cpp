#include "config.h"
#include "constants.h"
#include "config_reader.h"

#include <iostream>
#include <fstream>
#include <iomanip>

LaneData::LaneData()
{
    length = constants::lane::lengthDefault;
    limitVelocity = constants::lane::limitVelocityDefault;
    vehiclesPerMinute = constants::lane::vehiclesPerMinuteDefault;

    hasInputLane = false;
    inputLaneJunctionDistance = length / 2.;
    inputLaneLength = length;
    inputLaneLimitVelocity = limitVelocity;
    inputLaneVehiclesPerMinute = vehiclesPerMinute;
}

LaneData::LaneData(bool hasInput) : LaneData()
{
    hasInputLane = hasInput;
}

LaneData::LaneData(bool hasInput, float juncPoint) : LaneData(hasInput)
{
    inputLaneJunctionDistance = juncPoint;
}

LaneData::LaneData(float len, float limitVel, float vPerMin) : LaneData()
{
    length = len;
    limitVelocity = limitVel;
    vehiclesPerMinute = vPerMin;
}

LaneData::LaneData(float len, float limitVel, float vPerMin, bool hasInput, float juncPoint) : LaneData(len, limitVel, vPerMin)
{
    hasInputLane = hasInput;
    inputLaneJunctionDistance = juncPoint;
}

LaneData::LaneData(float len, float limitVel, float vPerMin, bool hasInput, float juncPoint, float inputLen, float inputLimitVel, float inputVPerMin) : LaneData(len, limitVel, vPerMin, hasInput, juncPoint)
{
    inputLaneLength = inputLen;
    inputLaneLimitVelocity = inputLimitVel;
    inputLaneVehiclesPerMinute = inputVPerMin;
}

void LaneData::Print()
{
    int width = 20;

    std::cout << std::left << std::setw(width) << "Length [m]" << std::setw(width) << "Max Velocity [km/h]" << std::setw(width) << "Vehicles Per Min" << std::setw(width) << "Has Input Lane ?" << std::setw(width) << "Junction Point [m]" << std::setw(width) << "Input Length [m]" << std::setw(30) << "Input Max Velocity [km/h]" << std::setw(30) << "Input Vehicles Per Min" << std::endl;
    std::cout << std::left << std::setw(width) << length << std::setw(width) << limitVelocity << std::setw(width) << vehiclesPerMinute << std::setw(width) << hasInputLane;

    if (hasInputLane)
    {
        std::cout << std::setw(width) << inputLaneJunctionDistance << std::setw(width) << inputLaneLength << std::setw(30) << inputLaneLimitVelocity << std::setw(30) << inputLaneVehiclesPerMinute << std::endl;
    } 
    else
    {
        std::cout << std::setw(width) << "/" << std::setw(width) << "/" << std::setw(30) << "/" << std::setw(30) << "/" << std::endl;
    }
}

Config* Config::instance = nullptr;

Config::Config()
{
    reader = new ConfigReader(this);
    InitSettings();
}

Config::~Config()
{
    instance = nullptr;
    delete reader;
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

void Config::LoadConfig(const std::string& fileName, const bool printInfo)
{
    if (printInfo)
    {
        std::cout << "Loading Config from file " << fileName << std::endl;
    }
    
    if (instance != nullptr)
    {
        instance->reader->Read(fileName);
    }
    else
    {
        GetConfig()->reader->Read(fileName);
    }
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
    Set(FloatSettings::CarLength, constants::car::lengthDefault);
    Set(FloatSettings::CarAcceleration, constants::car::accelerationDefault);
    Set(FloatSettings::CarDeceleration, constants::car::decelerationDefault);
    Set(FloatSettings::CarBrakingDistanceFactor, constants::car::brakingDistanceFactorDefault);
    Set(FloatSettings::CarAccelerationDistanceFactor, constants::car::accelDistanceFactorDefault);
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

    std::cout << std::endl << "* Lanes to simulate" << std::endl;
    std::cout << std::endl;

    int offset = 0;

    for (int i=0; i<lanesData.size(); i++)
    {
        std::cout << "** Lane(s) " << i + 1 + offset;
        if (lanesData[i].hasInputLane)
        {
            std::cout << " & " << i + 2 + offset;
            offset++;
        }
        std::cout << " **" << std::endl;
        lanesData[i].Print();
        std::cout << std::endl;
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

std::vector<LaneData> Config::GetLanesData() const
{
    return lanesData;
}

void Config::AddLane(const LaneData& lData)
{
    lanesData.push_back(lData);
}