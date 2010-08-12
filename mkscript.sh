#!/bin/bash

rm -rf themazegame
rm -rf build
mkdir build
cd build
cmake ..
make
cp src/themazegame ../
cd ../
