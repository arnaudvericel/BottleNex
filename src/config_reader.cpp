#include <iostream>
#include <fstream>

#include "utils.h"
#include "config_reader.h"
#include "config.h"

ConfigReader::ConfigReader(Config* myConfig)
{
    config = myConfig;
}

void ConfigReader::Read(const std::string& file)
{
    std::string SimDirective = "# SIMULATION";
    std::string LaneDirective = "# LANE";
    std::string FactoryDirective = "# VEHICLE FACTORY";
    std::string CarDirective = "# CAR";

    std::ifstream input;
    std::string line;
    input.open(file);

    if (input.is_open())
    {
        while(std::getline(input, line))
        {
            if (line.find(SimDirective) != std::string::npos)
            {
                std::getline(input, line);
                ParseSimulationData(line);
            }
            else if (line.find(CarDirective) != std::string::npos)
            {
                std::getline(input, line);
                ParseCarData(line);
            }
            else if (line.find(LaneDirective) != std::string::npos)
            {
                std::getline(input, line);
                ParseLaneData(line);
            }
            else if (line.find(FactoryDirective) != std::string::npos)
            {
                std::getline(input, line);
                ParseVehicleFactoryData(line);
            }
        }
    }

    input.close();
}

void ConfigReader::ParseSimulationData(const std::string& line)
{
    std::vector<std::string> simData = GetSplittedLine(line);

    if (simData.size() < 3)
    {
        std::cout << "Found " << simData.size() << " parameters after a SIMULATION directive" << std::endl;
        throw std::logic_error("# SIMULATION directive should contain 3 fields separated by <;> : maxTimeMin; CFLFactor; NbDumps");
    }

    float maxTime = std::stof(simData[0]);
    float CFLFactor = std::stof(simData[1]);
    int nbDumps = std::stoi(simData[2]);

    config->Set(Config::FloatSettings::MaxTimeMin, maxTime);
    config->Set(Config::FloatSettings::FactorCFL, CFLFactor);
    config->Set(Config::IntSettings::NbDumps, nbDumps);
}

void ConfigReader::ParseVehicleFactoryData(const std::string& line)
{
    std::vector<std::string> factoryData = GetSplittedLine(line);

    if (factoryData.size() < 2)
    {
        std::cout << "Found " << factoryData.size() << " parameters after a VEHICLE FACTORY directive" << std::endl;
        throw std::logic_error("# VEHICLE FACTORY directive should contain 2 fields separated by <;> : initFactorMin; initFactorMax");
    }

    int factorMin = std::stoi(factoryData[0]);
    int factorMax = std::stoi(factoryData[1]);

    config->Set(Config::FloatSettings::FactoryFactorMin, factorMin);
    config->Set(Config::FloatSettings::FactoryFactorMax, factorMax);
}

void ConfigReader::ParseCarData(const std::string& line)
{
    std::vector<std::string> carData = GetSplittedLine(line);

    if (carData.size() != 3 && carData.size() < 7)
    {
        std::cout << "Found " << carData.size() << " parameters after a CAR directive" << std::endl;
        throw std::logic_error("# CAR directive should contain 3 or 7 fields separated by <;> : length; max accel; max decel; brake distance factory; accel distance factor; init velocity factor; enter lane distance factor");
    }

    config->Set(Config::FloatSettings::CarLength, std::stof(carData[0]));
    config->Set(Config::FloatSettings::CarAcceleration, std::stof(carData[1]));
    config->Set(Config::FloatSettings::CarDeceleration, std::stof(carData[2]));

    if (carData.size() >= 7)
    {
        config->Set(Config::FloatSettings::CarBrakingDistanceFactor, std::stof(carData[3]));
        config->Set(Config::FloatSettings::CarAccelerationDistanceFactor, std::stof(carData[4]));
        config->Set(Config::FloatSettings::CarStartVelocityFactor, std::stof(carData[5]));
        config->Set(Config::FloatSettings::CarSafeDistanceToEnterLaneFactor, std::stof(carData[6]));
    }
}

void ConfigReader::ParseLaneData(const std::string& line)
{
    std::vector<std::string> laneData = GetSplittedLine(line);

    if (laneData.size() != 3 && laneData.size() != 4 && laneData.size() < 8)
    {
        std::cout << "Found " << laneData.size() << " parameters after a LANE directive" << std::endl;
        throw std::logic_error("# LANE directive should contain 3, 4 or 8 fields separated by <;> : length; max velocity; vehicles per minute; has input lane; junction point; input length, input max velocity; input vehicles per minute");
    }

    LaneData data = LaneData(std::stof(laneData[0]), std::stof(laneData[1]), std::stof(laneData[2]));

    if (laneData.size() > 3)
    {
        data.hasInputLane = std::stoi(laneData[3]) == 1;
    }
    
    if (laneData.size() >= 8)
    {
        data.inputLaneJunctionDistance = std::stof(laneData[4]);
        data.inputLaneLength = std::stof(laneData[5]);
        data.inputLaneLimitVelocity = std::stof(laneData[6]);
        data.inputLaneVehiclesPerMinute = std::stof(laneData[7]);
    }

    config->AddLane(data);
}
