cmake_minimum_required(VERSION 3.26)
project(CS_203_Lab_5_Yide_Fang C)

set(CMAKE_C_STANDARD 11)

#  simple computer -- A simple computer that can run a program
add_executable(CS_203_Lab_5_Yide_Fang main.c
        mem.c
        mem.h
        cpu.c
        cpu.h
        INSTRUCTIONS.h)

#  test cpu
add_executable(unit_test_cpu
        cpu.c
        cpu.h
        INSTRUCTIONS.h
        unit_test_cpu.c)

#  test mem
add_executable(unit_test_mem
        mem.c
        mem.h
        unit_test_mem.c)