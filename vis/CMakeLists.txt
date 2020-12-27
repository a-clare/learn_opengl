cmake_minimum_required(VERSION 3.0)
project(vis)

add_library(vis
  src/Display.cpp
  src/ShaderLoader.cpp)
target_link_libraries(vis glfw glad glm)
# Include up to the include/ folder. This means for anyone including this 
# library has to put "vis/" infront. Helps with understanding where includes
# are coming from
target_include_directories(
  vis
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include)