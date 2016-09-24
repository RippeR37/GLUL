#!/bin/bash


git submodule update --init third_party/zlib
cd third_party/zlib
cmake . && make && sudo make install
