cmake_minimum_required(VERSION 2.7)
project(hw4 C)

set(CMAKE_C_STANDARD 11)

# Open all warnings and consider warnings as errors
set(CMAKE_C_FLAGS "-O2 -Werror -Wall -Wextra -Wpedantic -std=c11")

# Add executable
add_executable(main main.c function.c)
target_link_libraries(main m)
