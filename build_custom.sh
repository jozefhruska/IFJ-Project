#!/bin/bash
make clean
make sedlacek
if [ -f sedlacek ]
then
    echo "---------------------------------------------------------------------------------------------"
    echo "============================================================================================="
    echo "============================================================================================="
    echo "====================================== RUNNING PROGRAM ======================================"
    echo "============================================================================================="
    echo "============================================================================================="
    echo "---------------------------------------------------------------------------------------------"

    ./sedlacek test
    # ./sedlacek test_programms/07
    # diff <(./sedlacek ./test_programms/14) ./test_programms_output/14

fi