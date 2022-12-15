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

The code outputs a file for each lane. If the lane is an input lane toward another, its name is appended with the "_parent_X" suffix.

Each file contains the evolution of the traffic on that particular lane:

- Mean velocity of all vehicles.
- Mean density of vehicles.
- Men distance between vehicles.
- Number of vehicles that are accelerating.
- Number of vehicles that are braking.
- Number of vehicles that are cruising at a constant velocity.

---

## Installation:

To make the executable "bottlenew", make sure you have the g++ compiler and type:

```
make all
```
in the /build directory.

---

## Your first bottlenew simulation:

To execute bottlenex, the user needs to provide a command line argument that is the input config. file.

To launch your first bottlenex simulation, go to the `/build/` directory and type:

```
./bottlenex ../input_examples/test.cfg
```

which is going to launch the code with the example input config. file provided in /input_examples/.

---

## Command line output examples:

TODO

---

Enjoy!
