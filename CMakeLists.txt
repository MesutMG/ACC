cmake_minimum_required(VERSION 3.10)
project(ACC_Simulation C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(include)

set(SOURCES
    src/main.c
    src/physics.c
    src/acc_logic.c

)

add_executable(acc_sim ${SOURCES})
