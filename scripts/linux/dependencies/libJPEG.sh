#!/bin/bash


git submodule update --init third_party/libjpeg
cd third_party/libjpeg
./configure && make && sudo make install

