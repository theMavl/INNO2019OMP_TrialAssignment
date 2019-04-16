cmake_minimum_required(VERSION 3.12)
project(INNO2019OMP_TrialAssignment C)

set(CMAKE_C_STANDARD 99)

add_executable(INNO2019OMP_TrialAssignment main.c converter.h fs_operations.c fs_operations.h image_operations.c image_operations.h)
target_link_libraries(INNO2019OMP_TrialAssignment m)
