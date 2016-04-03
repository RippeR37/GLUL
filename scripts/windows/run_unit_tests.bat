@echo off
setlocal


echo "##########################"
echo "### RUNNING UNIT TESTS ###"
echo "##########################"

cd ..\..\tests\bin\
move "Unit tests.exe" "unit_tests.exe" # required to have no space in name
unit_tests.exe
