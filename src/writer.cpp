#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

#include "vehicle.h"
#include "writer.h"
#include "lane.h"
#include "utils.h"
#include "enums.h"
#include "constants.h"

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
    fileName = "lane_" + strId.str();

    if (lane->HasParentLane())
    {
        std::stringstream parentLaneStrId;
        parentLaneStrId << lane->GetParentLane()->GetId();
        fileName += "_parent_" + parentLaneStrId.str();
    }

    fileName += constants::files::extension;
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
    AddColumn(out, 20, 8, lane->GetNbVehiclesOnLane());
    AddColumn(out, 30, 8, GetMeanVelocity() * 3.6);
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
    AddColumn(out, 30, 8, "Mean Velocity [km/h]");
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
    int counter = 0;
    float meanVelocity = 0.;
    std::vector<Vehicle*> vehiclesOnLane = lane->GetVehiclesOnLane();
    
    for (Vehicle* vehicle : vehiclesOnLane)
    {
        meanVelocity += vehicle->GetCurrentVelocity();
        counter++;
    } 
    
    if (counter != 0)
    {
        meanVelocity /= counter;
    }

    return meanVelocity;
}