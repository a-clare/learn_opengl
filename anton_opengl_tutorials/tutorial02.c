#include "gl_utils.h"
#include <stdio.h>

int main() {
  GLFWwindow* win = gl_start_win("Tutorial 02 - Shaders", 640, 480);

  while (!glfwWindowShouldClose(win)) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
    glfwSwapBuffers(win);
  }
}