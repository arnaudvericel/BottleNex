#include <iostream>

#include "../include/road.h"
#include "../include/car.h"

int main(int argc, char** argv)
{

    Road* road = new Road(1);

    road->Evolve();

    delete road;

    return 0;
}