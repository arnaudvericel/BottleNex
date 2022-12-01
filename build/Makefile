CC = g++
FLAGS = -g -Wall -std=c++11

SDIR = ../src
IDIR = ../include

###################################

bottlenex: bottlenex.o vehicle.o lane.o car.o road.o
	$(CC) $(FLAGS) -o bottlenex bottlenex.o vehicle.o lane.o car.o road.o

vehicle.o: $(SDIR)/vehicle.cpp $(IDIR)/vehicle.h
	$(CC) $(FLAGS) -o vehicle.o -c $(SDIR)/vehicle.cpp

lane.o: $(SDIR)/lane.cpp $(IDIR)/lane.h
	$(CC) $(FLAGS) -o lane.o -c $(SDIR)/lane.cpp

car.o: $(SDIR)/car.cpp $(IDIR)/car.h
	$(CC) $(FLAGS) -o car.o -c $(SDIR)/car.cpp

bottlenex.o:
	$(CC) $(FLAGS) -o bottlenex.o -c $(SDIR)/bottlenex.cpp

road.o: $(SDIR)/road.cpp $(IDIR)/road.h
	$(CC) $(FLAGS) -o road.o -c $(SDIR)/road.cpp

###################################

all: bottlenex clean

clean:
	rm *.o
