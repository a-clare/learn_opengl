cmake_minimum_required(VERSION 3.17)
project(learn_opengl_examples)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(tutorials)

add_executable(ie_ogl main.cpp)
target_link_libraries(ie_ogl glfw glad)

add_executable(cursor_position cursor_position.cpp)
target_link_libraries(cursor_position glfw glad)

add_executable(two_windows two_windows.cpp)
target_link_libraries(two_windows glfw glad)

add_executable(triangle triangle.cpp)
target_link_libraries(triangle glfw glad)

add_executable(rectangle rectangle.cpp)
target_link_libraries(rectangle glfw glad)

add_executable(two_color_triangle two_color_triangle.cpp)
target_link_libraries(two_color_triangle glfw glad)

add_executable(changing_color changing_color.cpp)
target_link_libraries(changing_color glfw glad)

add_executable(display_texture display_texture.cpp)
target_link_libraries(display_texture glfw glad)

add_executable(camera_zoom camera_zoom.cpp)
target_link_libraries(camera_zoom glfw glad glm)