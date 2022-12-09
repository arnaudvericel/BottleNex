#!/bin/bash

# Generates the test suite runner with cxxtestgen and compiles it.
# The output runner exec is placed in $EXE_DIR.

EXE_DIR="../build"
SRC_DIR="../src"
TEST_DIR="../test_src"

RUNNER_EXE="testRunner.exe"
RUNNER_CPP="testRunner.cpp"

if [[ "x$CXXTEST" -eq "x" ]]
then
    CXXTEST=$TEST_DIR
fi

export PATH=$CXXTEST/bin:$PATH

# todo : add runner options
# @generating test runner file
cxxtestgen --xunit-printer -w BottleNex --have-eh -o $TEST_DIR/$RUNNER_CPP $TEST_DIR/test_road.h $TEST_DIR/test_config.h

# todo : refactor
# @compile test runner file
g++ -std=c++11 -o $EXE_DIR/$RUNNER_EXE -I$CXXTEST $TEST_DIR/$RUNNER_CPP $SRC_DIR/road.cpp $SRC_DIR/lane.cpp $SRC_DIR/car.cpp $SRC_DIR/vehicle.cpp $SRC_DIR/writer.cpp $SRC_DIR/utils.cpp $SRC_DIR/config.cpp

$EXE_DIR/$RUNNER_EXE --help-tests