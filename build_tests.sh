#!/bin/bash
clear
make clean
make debug
if [ -f compilator_debug ]
then
    echo "---------------------------------------------------------------------------------------------"
    echo "============================================================================================="
    echo "============================================================================================="
    echo "======================================= RUNNING TESTS ======================================="
    echo "============================================================================================="
    echo "============================================================================================="
    echo "---------------------------------------------------------------------------------------------"

    ./compilator_debug test_programms/01
    ./compilator_debug test_programms/02
    ./compilator_debug test_programms/03
    ./compilator_debug test_programms/04
    ./compilator_debug test_programms/05
    ./compilator_debug test_programms/06
    ./compilator_debug test_programms/07
    ./compilator_debug test_programms/08
    ./compilator_debug test_programms/09
    ./compilator_debug test_programms/10
    ./compilator_debug test_programms/11
    ./compilator_debug test_programms/12
    ./compilator_debug test_programms/13
    ./compilator_debug test_programms/14
    ./compilator_debug test_programms/15
    ./compilator_debug test_programms/16
    ./compilator_debug test_programms/17
    ./compilator_debug test_programms/18
    ./compilator_debug test_programms/19
    ./compilator_debug test_programms/20
    ./compilator_debug test_programms/21
    ./compilator_debug test_programms/22
    ./compilator_debug test_programms/23
    ./compilator_debug test_programms/24
    ./compilator_debug test_programms/25
    ./compilator_debug test_programms/26
    ./compilator_debug test_programms/27
    ./compilator_debug test_programms/28
    ./compilator_debug advanced_tests/valid_programs/1.rb
    ./compilator_debug advanced_tests/valid_programs/2.rb
    ./compilator_debug advanced_tests/valid_programs/3.rb
    ./compilator_debug advanced_tests/valid_programs/4.rb
    ./compilator_debug advanced_tests/valid_programs/5.rb
    ./compilator_debug advanced_tests/valid_programs/6.rb
    ./compilator_debug advanced_tests/valid_programs/7.rb
    ./compilator_debug advanced_tests/valid_programs/8.rb
    ./compilator_debug advanced_tests/valid_programs/9.rb
    ./compilator_debug advanced_tests/valid_programs/10.rb
    ./compilator_debug advanced_tests/valid_programs/11.rb
    ./compilator_debug advanced_tests/valid_programs/12.rb
    ./compilator_debug advanced_tests/valid_programs/13.rb
    ./compilator_debug advanced_tests/valid_programs/14.rb
    ./compilator_debug advanced_tests/valid_programs/15.rb
    ./compilator_debug advanced_tests/valid_programs/16.rb
    ./compilator_debug advanced_tests/valid_programs/17.rb
    ./compilator_debug advanced_tests/valid_programs/function_call.rb
    ./compilator_debug advanced_tests/valid_programs/sample1.rb
    ./compilator_debug advanced_tests/valid_programs/sample2.rb
    ./compilator_debug advanced_tests/valid_programs/sample3.rb
    ./compilator_debug advanced_tests/valid_programs/stat1.rb
    ./compilator_debug advanced_tests/valid_programs/stat2.rb
    ./compilator_debug advanced_tests/valid_programs/stat3.rb

    echo
    echo "=================================== SHOULD FAIL (ERRCODE = 1) ======================================"
    echo
    ./compilator_debug advanced_tests/return_value_1/1.rb
    ./compilator_debug advanced_tests/return_value_1/2.rb
    ./compilator_debug advanced_tests/return_value_1/3.rb
    ./compilator_debug advanced_tests/return_value_1/4.rb
    ./compilator_debug advanced_tests/return_value_1/5.rb

    echo
    echo "=================================== SHOULD FAIL (ERRCODE = 2) ======================================"
    echo
    ./compilator_debug advanced_tests/return_value_2/1.rb
    ./compilator_debug advanced_tests/return_value_2/2.rb
    ./compilator_debug advanced_tests/return_value_2/3.rb
    ./compilator_debug advanced_tests/return_value_2/4.rb
    ./compilator_debug advanced_tests/return_value_2/5.rb
    ./compilator_debug advanced_tests/return_value_2/6.rb
    ./compilator_debug advanced_tests/return_value_2/7.rb
    ./compilator_debug advanced_tests/return_value_2/8.rb
    ./compilator_debug advanced_tests/return_value_2/9.rb
    ./compilator_debug advanced_tests/return_value_2/10.rb
    ./compilator_debug advanced_tests/return_value_2/11.rb
    ./compilator_debug advanced_tests/return_value_2/identifs.rb

    echo
    echo "=================================== SHOULD FAIL (ERRCODE = 3) ======================================"
    echo
    ./compilator_debug advanced_tests/return_value_3/1.rb
    ./compilator_debug advanced_tests/return_value_3/2.rb
    ./compilator_debug advanced_tests/return_value_3/3.rb
    ./compilator_debug advanced_tests/return_value_3/4.rb
    ./compilator_debug advanced_tests/return_value_3/5.rb
    ./compilator_debug advanced_tests/return_value_3/6.rb
    ./compilator_debug advanced_tests/return_value_3/7.rb
    ./compilator_debug advanced_tests/return_value_3/8.rb
    ./compilator_debug advanced_tests/return_value_3/9.rb
    ./compilator_debug advanced_tests/return_value_3/10.rb
    ./compilator_debug advanced_tests/return_value_3/11.rb
    ./compilator_debug advanced_tests/return_value_3/12.rb
    ./compilator_debug advanced_tests/return_value_3/13.rb
    ./compilator_debug advanced_tests/return_value_3/14.rb
    ./compilator_debug advanced_tests/return_value_3/15.rb
    ./compilator_debug advanced_tests/return_value_3/16.rb
    ./compilator_debug advanced_tests/return_value_3/17.rb
    ./compilator_debug advanced_tests/return_value_3/olok.rb

    echo
    echo "=================================== SHOULD FAIL (ERRCODE = 5) ======================================"
    echo
    ./compilator_debug advanced_tests/return_value_5/1.rb
    ./compilator_debug advanced_tests/return_value_5/2.rb
    ./compilator_debug advanced_tests/return_value_5/3.rb
    ./compilator_debug advanced_tests/return_value_5/4.rb
    ./compilator_debug advanced_tests/return_value_5/5.rb

		echo
    echo "=================================== GENERATOR ======================================"
    echo
		./ic18int <(./compilator_debug test_programms/01)
		./ic18int <(./compilator_debug test_programms/02)
		./ic18int <(./compilator_debug test_programms/03)
		./ic18int <(./compilator_debug test_programms/04)
		./ic18int <(./compilator_debug test_programms/05)
		./ic18int <(./compilator_debug test_programms/06)
		./ic18int <(./compilator_debug test_programms/07)
		./ic18int <(./compilator_debug test_programms/08)
		./ic18int <(./compilator_debug test_programms/09)
		./ic18int <(./compilator_debug test_programms/10)
fi