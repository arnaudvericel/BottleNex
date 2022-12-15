# BottleNex
--- 

BottleNex is a tool that simulates traffic evolution on roads, particularly traffic-jams.

It is modular so that the user can specify the road layout and the vehicles behaviour with an input configuration file.

The code also has unit tests and passes them all (see. the .xml report file in the /scripts/ repository).

---

The code requires an input files. Examples of such files are in the /input_examples/ directory. The user can configurate 4 main fields:

- The lane layout with the # LANE directive (multiple # LANE directives can be on the same config. file).
- The cars behaviour with the # CAR directive.
- The vehicle factory parameters with the # VEHICLE FACTORY directive.
- The simulation parameters with the # SIMULATION directive.

---

The code outputs a file for each lane. If the lane is an input lane towards another, its name is appended with the "_parent_X" suffix.

Each file contains the evolution of the traffic on that particular lane:

- Mean velocity of all vehicles.
- Mean density of vehicles.
- Men distance between vehicles.
- Number of vehicles that are accelerating.
- Number of vehicles that are braking.
- Number of vehicles that are cruising at a constant velocity.

---

## Installation:

To make the executable "bottlenex", make sure you have the g++ compiler and type:

```
make all
```
in the /build directory.

---

## Your first bottlenex simulation:

To execute bottlenex, the user needs to provide a command line argument that is the input config. file.

To launch your first bottlenex simulation, go to the `/build/` directory and type:

```
./bottlenex ../input_examples/test.cfg
```

which is going to launch the code with the example input configuration file provided in /input_examples/.

---

## Command line output examples:

Arnaud@mbp-de-arnaud:~/Documents/Codes.nosync/BottleNex/build
 : ./bottlenex.exe ../input_examples/test.cfg 
Loading Config from file ../input_examples/test.cfg
*********************
*** Configuration ***
*********************

Name                                -> Value     Unit      
----------------------------------------------------------
MaxTimeMin                          -> 30        min       
FactorCFL                           -> 1         /         
CarLength                           -> 5         m         
CarAcceleration                     -> 5         m/s^2     
CarDeceleration                     -> 15        m/s^2     
CarBrakingDistanceFactor            -> 2.5       /         
CarAccelerationDistanceFactor       -> 7.5       /         
CarStartVelocityFactor              -> 0.5       /         
CarSafeDistanceToEnterLaneFactor    -> 2         /         
FactoryFactorMin                    -> 60        /         
FactoryFactorMax                    -> 140       /         
NbDumps                             -> 500       /         

* Lanes to simulate

** Lane(s) 1 & 2 **
Length [m]          Max Velocity [km/h] Vehicles Per Min    Has Input Lane ?    Junction Point [m]  Input Length [m]    Input Max Velocity [km/h]     Input Vehicles Per Min        
5000                130                 40                  1                   1500                1000                70                            20                            

[====================================================================================================] 100 %

---

Enjoy!
