#ifndef CAR_H
#define CAR_H

#include "vehicle.h"

class Car : public Vehicle
{
public:
    constexpr static float MaxVelocity = 130. / 3.6; // m/s
    constexpr static float Acceleration = 40; // m/s^2
    constexpr static float Length = 5.; // m

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