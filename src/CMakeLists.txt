cmake_minimum_required(VERSION 3.5)

project(led C)

file (GLOB_RECURSE SOURCES "*.c")
file (GLOB_RECURSE HEADERS "../include/led/*.h")
file (GLOB_RECURSE LIBS    "../lib/*.*")

set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Wpedantic")
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/../include
  ${CMAKE_CURRENT_LIST_DIR}/../include/led
  ${GLEW_INCLUDE_DIRS}
)
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
add_executable(led ${SOURCES} ${HEADERS})
target_link_libraries(led ${LIBS} ${OPENGL_LIBRARY} ${GLEW_LIBRARIES})