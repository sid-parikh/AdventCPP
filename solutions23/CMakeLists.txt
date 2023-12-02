add_library(solutions_23 STATIC
        days.hpp
        day01.cpp
        day02.cpp
        input_utils.hpp
)

target_include_directories(solutions_23 PUBLIC .)