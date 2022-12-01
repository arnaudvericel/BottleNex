#ifndef CAR_H
#define CAR_H

#include "vehicle.h"

class Car : public Vehicle
{
public:
    constexpr static float MaxSpeed = 110.;
    constexpr static float MaxAcceleration = 5.;
    constexpr static float Length = 5.;

public:
    Car();
    ~Car() = default;
};

#endif