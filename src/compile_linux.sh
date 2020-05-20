#!/bin/bash
set -x
g++ -Wall -Wextra -std=c++11 -pthread board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp -o arduino
