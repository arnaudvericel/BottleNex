#include <cstdlib>
#include <iostream>
#include "time.h"

#include "vehicle_factory.h"
#include "car.h"
#include "config.h"

VehicleFactory::VehicleFactory()
{
    srand(time(NULL));
    Config* config = Config::GetConfig();
    initVelocityFactorMin = (*config)[Config::FloatSettings::FactoryFactorMin]; 
    initVelocityFactorMax = (*config)[Config::FloatSettings::FactoryFactorMax]; ;
}

VehicleFactory::VehicleFactory(int initFactorMin, int initFactorMax)
{
    srand(time(NULL));
    initVelocityFactorMin = initFactorMin;
    initVelocityFactorMax = initFactorMax;
}

Vehicle* VehicleFactory::Build(const VehicleType& vehicleType)
{
    int delta = initVelocityFactorMax - initVelocityFactorMin + 1;
    float velocityMultiplier = (float)(rand() % delta + initVelocityFactorMin) / 100.;

    switch (vehicleType)
    {
    case VehicleType::Car:
        return new Car(velocityMultiplier);
        break;
    
    default:
        return nullptr;
        break;
    }
}

int VehicleFactory::GetInitVelocityFactorMin() const
{
    return initVelocityFactorMin;
}

int VehicleFactory::GetInitVelocityFactoryMax() const
{
    return initVelocityFactorMax;
}