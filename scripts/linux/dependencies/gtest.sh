#!/bin/bash


sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake . && sudo make && sudo mv libgtest* /usr/lib/

