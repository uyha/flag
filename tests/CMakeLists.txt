add_executable(tests main.cpp)
target_link_libraries(tests PRIVATE river::flag)
if(MSVC)
  target_compile_options(tests PRIVATE /permissive- /W4 /WX /w14640 /w14242 /w14826)
else()
	target_compile_options(tests PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Werror)
endif()
add_test(tests tests)