project(adventofcode)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp)

add_custom_target(
        clang-format
        COMMAND /usr/bin/clang-format
        -style=file
        -i
        ${ALL_SOURCE_FILES}
)

add_custom_target(
        clang-tidy
        COMMAND /usr/bin/clang-tidy
        ${ALL_SOURCE_FILES}
        -config=''
        -fix
        --
        -std=c++17
        ${INCLUDE_DIRECTORIES}
)

add_executable(day1 day1/solve.cpp)
add_executable(day2 day2/solve.cpp)
add_executable(day3 day3/solve.cpp)
add_executable(day4 day4/solve.cpp)
add_executable(day5 day5/solve.cpp)
add_executable(day6 day6/solve.cpp)