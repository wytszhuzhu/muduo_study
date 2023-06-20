#!/bin/bash
rm -rf build
cmake -B build
cmake --build build -j 4 
