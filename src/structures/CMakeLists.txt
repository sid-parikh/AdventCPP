add_library(structures STATIC
        my_queue.hpp
        my_queue.cpp
)
target_include_directories(structures PUBLIC .)