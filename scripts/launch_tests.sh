#!/bin/bash

# Generates the testRunner exec and runs it.

EXE_DIR="../build"
RUNNER_EXE="testRunner.exe"

./gen_test_runner.sh

$EXE_DIR/$RUNNER_EXE

rm -rf lane*.dat