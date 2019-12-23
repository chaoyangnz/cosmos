#!/usr/bin/env bash

cd build
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B build/release .
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B build/debug .

cd build/debug
make