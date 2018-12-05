#!/bin/bash
clear
make clean
make demel
if [ -f demel ]
then
    echo "---------------------------------------------------------------------------------------------"
    echo "============================================================================================="
    echo "============================================================================================="
    echo "======================================= RUNNING TESTS ======================================="
    echo "============================================================================================="
    echo "============================================================================================="
    echo "---------------------------------------------------------------------------------------------"

    ./demel test_programms/01
    ./demel test_programms/02
    ./demel test_programms/03
    ./demel test_programms/04
    ./demel test_programms/05
    ./demel test_programms/06
    ./demel test_programms/07
    ./demel test_programms/08
    ./demel test_programms/09
    ./demel test_programms/10
    ./demel test_programms/11
    ./demel test_programms/12
    ./demel test_programms/13
    ./demel test_programms/14
    ./demel test_programms/15
    ./demel test_programms/16
    ./demel test_programms/17
    ./demel test_programms/18
    ./demel test_programms/19
    ./demel test_programms/20
    ./demel test_programms/21
    ./demel test_programms/22
    ./demel test_programms/23
    ./demel test_programms/24
    ./demel test_programms/25
    ./demel test_programms/26
    ./demel test_programms/27
    ./demel test_programms/28
    ./demel advanced_tests/valid_programs/1.rb
    ./demel advanced_tests/valid_programs/2.rb
    ./demel advanced_tests/valid_programs/3.rb
    ./demel advanced_tests/valid_programs/4.rb
    ./demel advanced_tests/valid_programs/5.rb
    ./demel advanced_tests/valid_programs/6.rb
    ./demel advanced_tests/valid_programs/7.rb
    ./demel advanced_tests/valid_programs/8.rb
    ./demel advanced_tests/valid_programs/9.rb
    ./demel advanced_tests/valid_programs/10.rb
    ./demel advanced_tests/valid_programs/11.rb
    ./demel advanced_tests/valid_programs/12.rb
    ./demel advanced_tests/valid_programs/13.rb
    ./demel advanced_tests/valid_programs/14.rb
    ./demel advanced_tests/valid_programs/15.rb
    ./demel advanced_tests/valid_programs/16.rb
    ./demel advanced_tests/valid_programs/17.rb
    ./demel advanced_tests/valid_programs/function_call.rb
    ./demel advanced_tests/valid_programs/sample1.rb
    ./demel advanced_tests/valid_programs/sample2.rb
    ./demel advanced_tests/valid_programs/sample3.rb
    ./demel advanced_tests/valid_programs/stat1.rb
    ./demel advanced_tests/valid_programs/stat2.rb
    ./demel advanced_tests/valid_programs/stat3.rb
    

    echo
    echo "=================================== SHOULD FAIL (ERRCODE = 1) ======================================"
    echo
    ./demel advanced_tests/return_value_1/1.rb
    ./demel advanced_tests/return_value_1/2.rb
    ./demel advanced_tests/return_value_1/3.rb
    ./demel advanced_tests/return_value_1/4.rb
    ./demel advanced_tests/return_value_1/5.rb

    echo
    echo "=================================== SHOULD FAIL (ERRCODE = 2) ======================================"
    echo
    ./demel advanced_tests/return_value_2/1.rb
    ./demel advanced_tests/return_value_2/2.rb
    ./demel advanced_tests/return_value_2/3.rb
    ./demel advanced_tests/return_value_2/4.rb
    ./demel advanced_tests/return_value_2/5.rb
    ./demel advanced_tests/return_value_2/6.rb
    ./demel advanced_tests/return_value_2/7.rb
    ./demel advanced_tests/return_value_2/8.rb
    ./demel advanced_tests/return_value_2/9.rb
    ./demel advanced_tests/return_value_2/10.rb
    ./demel advanced_tests/return_value_2/11.rb
    ./demel advanced_tests/return_value_2/identifs.rb

    echo
    echo "=================================== SHOULD FAIL (ERRCODE = 3) ======================================"
    echo
    ./demel advanced_tests/return_value_3/1.rb
    ./demel advanced_tests/return_value_3/2.rb
    ./demel advanced_tests/return_value_3/3.rb
    ./demel advanced_tests/return_value_3/4.rb
    ./demel advanced_tests/return_value_3/5.rb
    ./demel advanced_tests/return_value_3/6.rb
    ./demel advanced_tests/return_value_3/7.rb
    ./demel advanced_tests/return_value_3/8.rb
    ./demel advanced_tests/return_value_3/9.rb
    ./demel advanced_tests/return_value_3/10.rb
    ./demel advanced_tests/return_value_3/11.rb
    ./demel advanced_tests/return_value_3/12.rb
    ./demel advanced_tests/return_value_3/13.rb
    ./demel advanced_tests/return_value_3/14.rb
    ./demel advanced_tests/return_value_3/15.rb
    ./demel advanced_tests/return_value_3/16.rb
    ./demel advanced_tests/return_value_3/17.rb
    ./demel advanced_tests/return_value_3/olok.rb

    echo
    echo "=================================== SHOULD FAIL (ERRCODE = 5) ======================================"
    echo
    ./demel advanced_tests/return_value_5/1.rb
    ./demel advanced_tests/return_value_5/2.rb
    ./demel advanced_tests/return_value_5/3.rb
    ./demel advanced_tests/return_value_5/4.rb
    ./demel advanced_tests/return_value_5/5.rb
fi
