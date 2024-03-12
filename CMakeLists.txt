cmake_minimum_required (VERSION 3.8)
project (vk_test)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(vk_test
    src/main.cpp
    src/bmp.cpp)

if(WIN32)
    target_link_libraries(vk_test ${ALL_LIBS})
else()
    target_link_libraries(vk_test ${ALL_LIBS} pthread)
endif()

if(MSVC)
  target_compile_options(vk_test PRIVATE /W4 /WX)
else()
  target_compile_options(vk_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
