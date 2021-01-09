project(random_examples)

add_executable(simple_graph simple_graph.cpp)
target_link_libraries(simple_graph vis)
add_executable(display_gl_settings display_gl_settings)
target_link_libraries(display_gl_settings vis)

add_executable(simple_graph2 simple_graph2.cpp)
target_link_libraries(simple_graph2 vis)

add_executable(graph graph.cpp)
target_link_libraries(graph glfw glad)