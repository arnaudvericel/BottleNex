#ifndef CAR_H
#define CAR_H

#include "vehicle.h"

class Car : public Vehicle
{
public:
    constexpr static const float MaxSpeed = 110.;
    constexpr static const float MaxAcceleration = 5.;
    constexpr static const float Length = 5.;

public:
    Car();
    ~Car() = default;

    virtual void Move() override;
};

#endif