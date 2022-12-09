#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

const std::string ConfigFloatSettingsName[] = { "MaxTimeMin", "CondCFL", "LaneLimitVelocity", "LaneLength", "CarMaxVelocity", "CarLength", "CarAcceleration", 
    "CarDeceleration", "VehiclesPerMinute", "CarBrakingDistanceFactor", "CarCruisingDistanceFactor", "CarAccelerationDistanceFactor", "CarStartVelocityFactor",
    "CarSafeDistanceToEnterLaneFactor" };
const std::string ConfigFloatSettingsUnit[] = { "min", "/", "km/h", "m", "km/h", "m", "m/s^2", "m/s^2", "per min", "/", "/", "/", "/", "/" };

const std::string ConfigIntSettingsName[] = { "NbDumps" };
const std::string ConfigIntSettingsUnit[] = { "/" };

class Config
{
public:
    enum class FloatSettings
    {
        MaxTimeMin,
        CondCFL,
        LaneLimitVelocity,
        LaneLength,
        CarMaxVelocity,
        CarLength,
        CarAcceleration,
        CarDeceleration,
        VehiclesPerMinute,
        CarBrakingDistanceFactor,
        CarCruisingDistanceFactor,
        CarAccelerationDistanceFactor,
        CarStartVelocityFactor,
        CarSafeDistanceToEnterLaneFactor
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
    //
    Config();
    void InitSettings();

public:
    ~Config();
    float& operator[](const FloatSettings&);
    int& operator[](const IntSettings&);
    void Set(const FloatSettings&, const float&);
    void Set(const IntSettings&, const int&);
    static Config* GetConfig();
    static void LoadConfig(std::string);
    void PrintConfig();
};

std::ostream& operator<<(std::ostream&, const Config::FloatSettings&);
std::ostream& operator<<(std::ostream&, const Config::IntSettings&);

#endif