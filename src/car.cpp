#include <iostream>
#include "../include/car.h"

Car::Car() : Vehicle(Length, MaxSpeed, MaxAcceleration) {}

void Car::Move()
{
    cout << "This Car is moving @ " << MaxSpeed << " km/h max!" << endl;
}
