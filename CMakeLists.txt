# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(AOC_2020)

# --- Define the Shared Library ---

# Add a library target
# STATIC means the code is compiled into an archive (.a or .lib) that is linked into executables.
add_library(
    AOC_Common
    STATIC
    lib/util.cpp
    # Add other library source files here
)

# Tell executables where to find the library's header files
# INTERFACE means this property is passed along to anything that links to AOC_Common
target_include_directories(
    AOC_Common
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# --- Define the Executable ---

# Add the executable target (unchanged from before)
add_executable(day1 day1/main.cpp)
add_executable(day2 day2/main.cpp)
add_executable(day3 day3/main.cpp)
add_executable(day4 day4/main.cpp)
add_executable(day5 day5/main.cpp)
add_executable(day6 day6/main.cpp)
add_executable(day7 day7/main.cpp)
add_executable(day8 day8/main.cpp)
add_executable(day9 day9/main.cpp)
add_executable(day10 day10/main.cpp)
add_executable(day11 day11/main.cpp)
add_executable(day12 day12/main.cpp)

# Link the executable to the library
# This step makes the library's functions available to the day19 executable.
target_link_libraries(
    day1
    AOC_Common
)
target_link_libraries(
    day2
    AOC_Common
)
target_link_libraries(
    day3
    AOC_Common
)
target_link_libraries(
    day4
    AOC_Common
)
target_link_libraries(
    day5
    AOC_Common
)
target_link_libraries(
    day6
    AOC_Common
)
target_link_libraries(
    day7
    AOC_Common
)
target_link_libraries(
    day8
    AOC_Common
)
target_link_libraries(
    day9
    AOC_Common
)
target_link_libraries(
    day10
    AOC_Common
)
target_link_libraries(
    day11
    AOC_Common
)
target_link_libraries(
    day12
    AOC_Common
)
