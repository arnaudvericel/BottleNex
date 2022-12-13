#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>

class Config;

class ConfigReader
{
private:
    Config* config;

    void ParseSimulationData(const std::string&);
    void ParseCarData(const std::string&);
    void ParseLaneData(const std::string&);
    void ParseVehicleFactoryData(const std::string&);

public:
    ConfigReader(Config*);
    ~ConfigReader() = default;

    void Read(const std::string&);
};

#endif