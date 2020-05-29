cmake_minimum_required(VERSION 3.8)
project("Flag" 
        VERSION 0.0 
        LANGUAGES CXX)

add_subdirectory(src)

if (${FLAG_INCLUDE_TESTS})
  message(STATUS "Including tests")
  add_subdirectory(tests)
endif()
