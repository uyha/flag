cmake_minimum_required(VERSION 3.8)
project("Flag" 
        VERSION 0.0 
        LANGUAGES CXX)

set(CXX_STANDARD 20)

add_subdirectory(include)

if (${FLAG_INCLUDE_EXAMPLES})
  message(STATUS "Including examples")
  enable_testing()
  add_subdirectory(examples)
endif()

if (${FLAG_INCLUDE_TESTS})
  message(STATUS "Including tests")
  enable_testing()
  add_subdirectory(tests)
endif()