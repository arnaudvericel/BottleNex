#include <iostream>
#include "../include/car.h"

int Car::nbActiveCars = 0;

Car::Car() : Vehicle(Length, MaxSpeed, MaxAcceleration)
{
    nbActiveCars++;
}

Car::~Car()
{
    nbActiveCars--;
}
