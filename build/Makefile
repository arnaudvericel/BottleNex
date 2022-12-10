CC = g++
FLAGS = -g -Wall -std=c++11

SDIR = ../src

###################################

bottlenex: bottlenex.o vehicle.o lane.o car.o road.o utils.o writer.o config.o vehicle_factory.o
	$(CC) $(FLAGS) -o bottlenex.exe bottlenex.o vehicle.o lane.o car.o road.o utils.o writer.o config.o vehicle_factory.o

vehicle.o: $(SDIR)/vehicle.cpp $(SDIR)/vehicle.h
	$(CC) $(FLAGS) -o vehicle.o -c $(SDIR)/vehicle.cpp

lane.o: $(SDIR)/lane.cpp $(SDIR)/lane.h
	$(CC) $(FLAGS) -o lane.o -c $(SDIR)/lane.cpp

car.o: $(SDIR)/car.cpp $(SDIR)/car.h
	$(CC) $(FLAGS) -o car.o -c $(SDIR)/car.cpp

bottlenex.o:
	$(CC) $(FLAGS) -o bottlenex.o -c $(SDIR)/bottlenex.cpp

road.o: $(SDIR)/road.cpp $(SDIR)/road.h
	$(CC) $(FLAGS) -o road.o -c $(SDIR)/road.cpp

utils.o: $(SDIR)/utils.cpp $(SDIR)/utils.h
	$(CC) $(FLAGS) -o utils.o -c $(SDIR)/utils.cpp

writer.o: $(SDIR)/writer.cpp $(SDIR)/writer.h
	$(CC) $(FLAGS) -o writer.o -c $(SDIR)/writer.cpp

config.o: $(SDIR)/config.cpp $(SDIR)/config.h
	$(CC) $(FLAGS) -o config.o -c $(SDIR)/config.cpp

vehicle_factory.o: $(SDIR)/vehicle_factory.cpp $(SDIR)/vehicle_factory.h
	$(CC) $(FLAGS) -o vehicle_factory.o -c $(SDIR)/vehicle_factory.cpp

###################################

all: bottlenex clean

clean:
	rm *.o
