# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
set(HEADER_LIST
        "${AdventCPP_SOURCE_DIR}/include/day01.hpp"
        "${AdventCPP_SOURCE_DIR}/include/day02.hpp"
)

configure_file("../input/day01"
        "${CMAKE_CURRENT_BINARY_DIR}/input/day01" COPYONLY)
# Make an automatic library - will be static or dynamic based on user setting
add_library(solutions_22 STATIC
        ${HEADER_LIST}
        input_utils.cpp
        input_utils.hpp
        day01.cpp
        day02.cpp
)

# We need this directory, and users of our library will need it too
target_include_directories(solutions_22 PUBLIC ../include)
