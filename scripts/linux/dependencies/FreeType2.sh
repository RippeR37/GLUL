#!/bin/bash


git submodule update --init third_party/freetype2
cd third_party/freetype2
cmake . -DBUILD_SHARED_LIBS:BOOL=true && sudo make install

