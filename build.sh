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

    if [ "$(diff <(./sedlacek ./test_programms/01) ./test_programms_output/01)" == "" ]
    then
        echo "Successfully done (prog 1)"
    else
        echo "Files in prog 1 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/02) ./test_programms_output/02)" == "" ]
    then
        echo "Successfully done (prog 2)"
    else
        echo "Files in prog 2 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/03) ./test_programms_output/03)" == "" ]
    then
        echo "Successfully done (prog 3)"
    else
        echo "Files in prog 3 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/04) ./test_programms_output/04)" == "" ]
    then
        echo "Successfully done (prog 4)"
    else
        echo "Files in prog 4 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/05) ./test_programms_output/05)" == "" ]
    then
        echo "Successfully done (prog 5)"
    else
        echo "Files in prog 5 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/06) ./test_programms_output/06)" == "" ]
    then
        echo "Successfully done (prog 6)"
    else
        echo "Files in prog 6 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/07) ./test_programms_output/07)" == "" ]
    then
        echo "Successfully done (prog 7)"
    else
        echo "Files in prog 7 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/08) ./test_programms_output/08)" == "" ]
    then
        echo "Successfully done (prog 8)"
    else
        echo "Files in prog 8 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/09) ./test_programms_output/09)" == "" ]
    then
        echo "Successfully done (prog 9)"
    else
        echo "Files in prog 9 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/10) ./test_programms_output/10)" == "" ]
    then
        echo "Successfully done (prog 10)"
    else
        echo "Files in prog 10 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/11) ./test_programms_output/11)" == "" ]
    then
        echo "Successfully done (prog 11)"
    else
        echo "Files in prog 11 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/12) ./test_programms_output/12)" == "" ]
    then
        echo "Successfully done (prog 12)"
    else
        echo "Files in prog 12 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/13) ./test_programms_output/13)" == "" ]
    then
        echo "Successfully done (prog 13)"
    else
        echo "Files in prog 13 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/14) ./test_programms_output/14)" == "" ]
    then
        echo "Successfully done (prog 14)"
    else
        echo "Files in prog 14 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/15) ./test_programms_output/15)" == "" ]
    then
        echo "Successfully done (prog 15)"
    else
        echo "Files in prog 15 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/16) ./test_programms_output/16)" == "" ]
    then
        echo "Successfully done (prog 16)"
    else
        echo "Files in prog 16 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/17) ./test_programms_output/17)" == "" ]
    then
        echo "Successfully done (prog 17)"
    else
        echo "Files in prog 17 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/18) ./test_programms_output/18)" == "" ]
    then
        echo "Successfully done (prog 18)"
    else
        echo "Files in prog 18 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/19) ./test_programms_output/19)" == "" ]
    then
        echo "Successfully done (prog 19)"
    else
        echo "Files in prog 19 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/20) ./test_programms_output/20)" == "" ]
    then
        echo "Successfully done (prog 20)"
    else
        echo "Files in prog 20 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/21) ./test_programms_output/21)" == "" ]
    then
        echo "Successfully done (prog 21)"
    else
        echo "Files in prog 21 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/22) ./test_programms_output/22)" == "" ]
    then
        echo "Successfully done (prog 22)"
    else
        echo "Files in prog 22 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/23) ./test_programms_output/23)" == "" ]
    then
        echo "Successfully done (prog 23)"
    else
        echo "Files in prog 23 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/24) ./test_programms_output/24)" == "" ]
    then
        echo "Successfully done (prog 14)"
    else
        echo "Files in prog 24 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/25) ./test_programms_output/25)" == "" ]
    then
        echo "Successfully done (prog 25)"
    else
        echo "Files in prog 25 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/26) ./test_programms_output/26)" == "" ]
    then
        echo "Successfully done (prog 26)"
    else
        echo "Files in prog 26 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/27) ./test_programms_output/27)" == "" ]
    then
        echo "Successfully done (prog 27)"
    else
        echo "Files in prog 27 differ"
    fi
    #====================================================================================
    if [ "$(diff <(./sedlacek ./test_programms/f_01) ./test_programms_output/f_01)" == "" ]
    then
        echo "Successfully done (prog f_01)"
    else
        echo "Files in prog f_01 differ"
    fi
    

    # ./sedlacek ./test_programms/01 > ./test_programms_output/01
    # ./sedlacek ./test_programms/02 > ./test_programms_output/02
    # ./sedlacek ./test_programms/03 > ./test_programms_output/03
    # ./sedlacek ./test_programms/04 > ./test_programms_output/04
    # ./sedlacek ./test_programms/05 > ./test_programms_output/05
    # ./sedlacek ./test_programms/06 > ./test_programms_output/06
    # ./sedlacek ./test_programms/07 > ./test_programms_output/07
    # ./sedlacek ./test_programms/08 > ./test_programms_output/08
    # ./sedlacek ./test_programms/09 > ./test_programms_output/09
    # ./sedlacek ./test_programms/10 > ./test_programms_output/10
    # ./sedlacek ./test_programms/11 > ./test_programms_output/11
    # ./sedlacek ./test_programms/12 > ./test_programms_output/12
    # ./sedlacek ./test_programms/13 > ./test_programms_output/13
    # ./sedlacek ./test_programms/14 > ./test_programms_output/14
    # ./sedlacek ./test_programms/15 > ./test_programms_output/15
    # ./sedlacek ./test_programms/16 > ./test_programms_output/16
    # ./sedlacek ./test_programms/17 > ./test_programms_output/17
    # ./sedlacek ./test_programms/18 > ./test_programms_output/18
    # ./sedlacek ./test_programms/19 > ./test_programms_output/19
    # ./sedlacek ./test_programms/20 > ./test_programms_output/20
    # ./sedlacek ./test_programms/21 > ./test_programms_output/21
    # ./sedlacek ./test_programms/22 > ./test_programms_output/22
    # ./sedlacek ./test_programms/23 > ./test_programms_output/23
    # ./sedlacek ./test_programms/24 > ./test_programms_output/24
    # ./sedlacek ./test_programms/25 > ./test_programms_output/25
    # ./sedlacek ./test_programms/26 > ./test_programms_output/26
    # ./sedlacek ./test_programms/27 > ./test_programms_output/27
    # ./sedlacek ./test_programms/f_01 > ./test_programms_output/f_01
fi