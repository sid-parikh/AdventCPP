add_executable(twenty_two twenty_two.cpp)
target_compile_features(twenty_two PRIVATE cxx_std_20)

target_link_libraries(twenty_two PRIVATE solutions_22)

add_executable(twenty_three twenty_three.cpp)
target_compile_features(twenty_three PRIVATE cxx_std_20)
target_link_libraries(twenty_three PRIVATE solutions_23)