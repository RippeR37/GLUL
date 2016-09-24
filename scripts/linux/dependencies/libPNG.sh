#!/bin/bash


git submodule update --init third_party/libpng
cd third_party/libpng
cmake . && make && sudo make install

