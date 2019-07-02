cmake_minimum_required(VERSION 3.5)

project(led C)

file (GLOB_RECURSE SOURCES "*.c")
file (GLOB_RECURSE HEADERS "../include/led/*.h")
file (GLOB_RECURSE LIBS    "../lib/*.*")

set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Wpedantic")

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/../include
  ${CMAKE_CURRENT_LIST_DIR}/../include/led
)
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
add_executable(led ${SOURCES} ${HEADERS})
target_link_libraries(led ${LIBS})