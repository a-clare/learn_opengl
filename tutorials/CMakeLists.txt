## Chapter 1
add_executable(ch1_hello_window ch1/hello_window.cpp)
target_link_libraries(ch1_hello_window vis)

## Chapter 2
add_executable(ch2_simple_triangle ch2/simple_triangle.cpp)
target_link_libraries(ch2_simple_triangle vis)
add_executable(ch2_simple_rectangle_index ch2/simple_rectangle_index.cpp)
target_link_libraries(ch2_simple_rectangle_index vis)