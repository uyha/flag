add_library(river-flag INTERFACE)
add_library(river::flag ALIAS river-flag)
target_include_directories(river-flag INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_features(river-flag INTERFACE cxx_std_20)