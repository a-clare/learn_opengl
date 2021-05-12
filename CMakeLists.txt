cmake_minimum_required(VERSION 3.0)
project(learn_opengl)

add_subdirectory(submodules/glad)
set(GLFW_BUILD_EXAMPLES ON)
add_subdirectory(submodules/glfw)
add_subdirectory(submodules/glm)

add_subdirectory(anton_opengl_tutorials)
add_subdirectory(vis)
add_subdirectory(random_examples)
add_subdirectory(learn_opengl_examples)
add_subdirectory(sb)