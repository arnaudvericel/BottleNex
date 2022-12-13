#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <vector>

const std::string ConfigFloatSettingsName[] = { "MaxTimeMin", "FactorCFL", "CarLength", "CarAcceleration", 
    "CarDeceleration", "CarBrakingDistanceFactor", "CarAccelerationDistanceFactor", "CarStartVelocityFactor",
    "CarSafeDistanceToEnterLaneFactor", "FactoryFactorMin", "FactoryFactorMax" };
const std::string ConfigFloatSettingsUnit[] = { "min", "/", "m", "m/s^2", "m/s^2", "/", "/", "/", "/", "/", "/" };

const std::string ConfigIntSettingsName[] = { "NbDumps" };
const std::string ConfigIntSettingsUnit[] = { "/" };

struct LaneData
{
    float length;
    float limitVelocity;
    float vehiclesPerMinute;
    bool hasInputLane;
    float inputLaneLength;
    float inputLaneLimitVelocity;
    float inputLaneJunctionDistance;
    float inputLaneVehiclesPerMinute;

    // TODO : create constructor overloads to facilitate configuration
    LaneData();
    LaneData(bool hasInput);
    LaneData(bool hasInput, float juncPoint);
    LaneData(float len, float limitVel, float vPerMin);
    LaneData(float len, float limitVel, float vPerMin, bool hasInput, float juncPoint);
    LaneData(float len, float limitVel, float vPerMin, bool hasInput, float juncPoint, float inputLen, float inputLimitVel, float inputVPerMin);
    ~LaneData() = default;
    void Print();
};

class ConfigReader;

class Config
{
public:
    enum class FloatSettings
    {
        MaxTimeMin,
        FactorCFL,
        CarLength,
        CarAcceleration,
        CarDeceleration,
        CarBrakingDistanceFactor,
        CarAccelerationDistanceFactor,
        CarStartVelocityFactor,
        CarSafeDistanceToEnterLaneFactor,
        FactoryFactorMin,
        FactoryFactorMax
    };
    enum class IntSettings
    {
        NbDumps
    };

private:
    typedef std::map<FloatSettings,float> FloatSettingsMap;
    typedef std::map<IntSettings,int> IntSettingsMap;
    FloatSettingsMap floatSettingsMap;
    IntSettingsMap intSettingsMap;
    static Config* instance;
    std::vector<LaneData> lanesData;
    ConfigReader* reader;
    //
    Config();
    void InitSettings();

public:
    ~Config();
    float& operator[](const FloatSettings&);
    int& operator[](const IntSettings&);
    void Set(const FloatSettings&, const float&);
    void Set(const IntSettings&, const int&);
    void AddLane(const LaneData&);
    //
    std::vector<LaneData> GetLanesData() const;
    static Config* GetConfig();
    //
    static void LoadConfig(const std::string&);
    void PrintConfig();
};

std::ostream& operator<<(std::ostream&, const Config::FloatSettings&);
std::ostream& operator<<(std::ostream&, const Config::IntSettings&);
Config::FloatSettings& operator++(Config::FloatSettings&);
Config::IntSettings& operator++(Config::IntSettings&);

#endif