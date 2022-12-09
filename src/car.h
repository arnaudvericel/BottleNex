#ifndef CAR_H
#define CAR_H

#include "vehicle.h"

class Car : public Vehicle
{
public:
    static int nbActiveCars;

    virtual void Brake(const float) override;
    virtual void Cruise(const float) override;
    virtual void Accelerate(const float) override;
    virtual void EvaluateMotionState(const float) override;

public:
    Car(float);
    ~Car();
};

#endif