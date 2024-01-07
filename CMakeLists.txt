# Created by Yide Fang
# Lab 3 for CS203
#

cmake_minimum_required(VERSION 3.25)
project(fish_haus C)

set(CMAKE_C_STANDARD 11)

# There are three differe executables produced by this project.

#  fish_haus     -- The actual game.
add_executable(fish_haus main.c bit_manip.c game.c file.c)

#  test_bitmanip -- Testing of the bit manipulation functions.
add_executable(test_binmanip test_bitmanip.c bit_manip.c)

#  test_game     -- A basic testing frome work to walk through the
#                   program at a high-level.
add_executable(test_game test_game.c bit_manip.c game.c)
