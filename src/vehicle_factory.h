#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H

#include "enums.h"

class Vehicle;
class Lane;

class VehicleFactory
{
private:
    int initVelocityFactorMin;
    int initVelocityFactorMax;

public:
    VehicleFactory();
    VehicleFactory(int, int);
    ~VehicleFactory() = default;
    Vehicle* Build(Lane*, const VehicleType&);
    int GetInitVelocityFactorMin() const;
    int GetInitVelocityFactoryMax() const;
};

#endif