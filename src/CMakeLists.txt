add_library(flag INTERFACE)
add_library(flag::flag ALIAS flag)
target_include_directories(flag INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_features(flag INTERFACE cxx_std_20)