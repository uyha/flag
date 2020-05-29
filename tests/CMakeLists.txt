add_executable(test main.cpp)
target_link_libraries(test PRIVATE flag)
target_compile_features(test PRIVATE cxx_std_20)