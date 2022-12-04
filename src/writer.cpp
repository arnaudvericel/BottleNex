#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

#include "../include/writer.h"
#include "../include/lane.h"
#include "../include/car.h"
#include "../include/utils.h"
#include "../include/enums.h"

Writer::Writer()
{
    InitVehiclesStats();
}

void Writer::Init(Lane* myLane)
{
    lane = myLane;
    SetFilename();

    if (fileExists(fileName))
    {
        DeleteFile();
    }
}

void Writer::DeleteFile()
{
    std::string command = "rm " + fileName;
    system(command.c_str());
}

void Writer::SetFilename()
{
    std::stringstream strId;
    strId << lane->GetId();
    fileName = "lane_" + strId.str() + ".dat";
}

void Writer::InitVehiclesStats()
{
    vehiclesAccelerating = 0;
    vehiclesBraking = 0;
    vehiclesCruising = 0;
}

void Writer::FetchVehiclesStats()
{
    InitVehiclesStats();
    
    for (Vehicle* vehicle : lane->GetVehiclesOnLane())
    {
        if (vehicle != nullptr)
        {
            switch (vehicle->GetMotionState())
            {
                case Motion::Accelerating:
                    vehiclesAccelerating++;
                    break;
                
                case Motion::Cruising:
                    vehiclesCruising++;
                    break;

                case Motion::Braking:
                    vehiclesBraking++;
                    break;
            
                default:
                    break;
            }
        }
    }
}

void Writer::WriteStep(const float time)
{
    if (!fileExists(fileName))
    {
        WriteHeader();
    }

    FetchVehiclesStats();

    std::fstream out;
    out.open(fileName, std::ios::out | std::ios::app);
    AddColumn(out, 10, 8, time);
    AddColumn(out, 20, 8, lane->GetNbVehiclesOnLane());
    AddColumn(out, 20, 8, lane->GetNbVehiclesOnLane()); // fixme : sort by vehicle type
    AddColumn(out, 30, 8, GetMeanVelocity());
    AddColumn(out, 30, 8, GetMeanDistance());
    AddColumn(out, 40, 8, GetMeanDensity());
    AddColumn(out, 30, 8, vehiclesCruising);
    AddColumn(out, 30, 8, vehiclesAccelerating);
    AddColumn(out, 30, 8, vehiclesBraking);
    out << std::endl;
    out.close();
}

void Writer::WriteHeader()
{
    std::fstream out;
    out.open(fileName, std::ios::out);
    AddColumn(out, 10, 8, "Time [s]");
    AddColumn(out, 20, 8, "Nb_Vehicles");
    AddColumn(out, 20, 8, "Nb_Cars");
    AddColumn(out, 30, 8, "Mean Velocity [m/s]");
    AddColumn(out, 30, 8, "Mean Vehicle Spacing [m]");
    AddColumn(out, 40, 8, "Mean Vehicle Density [unit/100m]");
    AddColumn(out, 30, 8, "Nb_Vehicles_Cruising");
    AddColumn(out, 30, 8, "Nb_Vehicles_Accelerating");
    AddColumn(out, 30, 8, "Nb_Vehicles_Braking");
    out << std::endl;
    out.close();
}

float Writer::GetMeanDensity() const
{
    return 100. * lane->GetNbVehiclesOnLane() / lane->GetLength();
}

float Writer::GetMeanDistance() const
{
    float meanDistance = 0.;
    int counter = 0;
    std::vector<Vehicle*> vehiclesOnLane = lane->GetVehiclesOnLane();

    for (Vehicle* vehicle : vehiclesOnLane)
    {
        if (vehicle->GetForwardVehicle() != nullptr)
        {
            meanDistance += vehicle->GetForwardVehicle()->GetDistanceInLane() - vehicle->GetDistanceInLane();
            counter++;
        }
    }
    if (counter > 0)
    {
        meanDistance /= counter;
    }

    return meanDistance;
}

float Writer::GetMeanVelocity() const
{
    float meanVelocity = 0.;
    std::vector<Vehicle*> vehiclesOnLane = lane->GetVehiclesOnLane();
    
    for (Vehicle* vehicle : vehiclesOnLane)
    {
        meanVelocity += vehicle->GetCurrentVelocity();
    } 
    
    if (vehiclesOnLane.size() > 1)
    {
        meanVelocity /= vehiclesOnLane.size() - 1;
    }

    return meanVelocity;
}