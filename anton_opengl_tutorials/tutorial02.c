#include "gl_utils.h"
#include <stdio.h>

int main() {
  GLFWwindow* win = gl_start_win("Tutorial 02 - Shaders", 640, 480);

  GLuint vs_shader = gl_load_vs_from_file("/Users/adam/Documents - Adam’s MacBook Pro/projects/learn_opengl/anton_opengl_tutorials/shaders/vs02.vs");
  
  while (!glfwWindowShouldClose(win)) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
    glfwSwapBuffers(win);
  }
}