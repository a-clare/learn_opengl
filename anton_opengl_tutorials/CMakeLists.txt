cmake_minimum_required(VERSION 3.10)
project(anton_opengl_tutorials)

set(all_examples
  tutorial00
  tutorial01
  tutorial02
  tutorial02_changing_color
  tutorial04)

foreach(example ${all_examples})
  add_executable(${example} "${example}.c" gl_utils.c)
  target_link_libraries(${example} glad glfw)
endforeach()