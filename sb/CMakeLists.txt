project(sb)

# Chapter 2
add_executable(simple_window simple_window/simple_window.cpp)
target_link_libraries(simple_window vis)

add_executable(single_point single_point/single_point.cpp)
target_link_libraries(single_point vis)

add_executable(single_triangle single_triangle/single_triangle.cpp)
target_link_libraries(single_triangle vis)

add_executable(animated_triangle animated_triangle/animated_triangle.cpp)
target_link_libraries(animated_triangle vis)

add_executable(color_triangle color_triangle/color_triangle.cpp)
target_link_libraries(color_triangle vis)