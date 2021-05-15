#include "gl_utils.h"
#include <stdio.h>

GLFWwindow* gl_start_win(const char* winName, int w, int h) {
  GLFWwindow* ret_win;
  printf("Starting GLFW %s\n", glfwGetVersionString());
  if (!glfwInit()) {
    printf("Error: Could not start GLFW\n");
    return NULL;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  ret_win = glfwCreateWindow(w, h, winName, NULL, NULL);
  if (ret_win == NULL) {
    printf("Error: Could not open window\n");
  }
  glfwMakeContextCurrent(ret_win);
  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Error: Could not initialize GLAD");
    return 0;
  }

  printf("Renderer %s\n", glGetString(GL_RENDERER));
  printf("Version %s\n", glGetString(GL_VERSION));

  return ret_win;
}