#!/bin/bash


git submodule update --init third_party/glfw
cd third_party/glfw
cmake -DBUILD_SHARED_LIBS=ON && sudo make install

