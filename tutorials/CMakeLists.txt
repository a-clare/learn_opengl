## Chapter 1
add_executable(hello_window hello_window.cpp)
target_link_libraries(hello_window vis)

## Chapter 2
add_executable(simple_triangle simple_triangle.cpp)
target_link_libraries(simple_triangle vis)
add_executable(simple_rectangle_index simple_rectangle_index.cpp)
target_link_libraries(simple_rectangle_index vis)
add_executable(colorful_triangle colorful_triangle.cpp)
target_link_libraries(colorful_triangle vis)

add_executable(textured_container textured_container.cpp)
target_link_libraries(textured_container vis)