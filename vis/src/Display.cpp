#include "vis/Display.h"

Display::Display(const std::string& windowName, std::uint16_t width, std::uint16_t height) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window_ = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
  glfwMakeContextCurrent(window_);
  glfwSetFramebufferSizeCallback(window_, &Display::ResizeCallback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    /* TODO: What to do on failure, probably throw an exception of some sort? */
    return;
  }
}

bool Display::Shutdown() const {
  if(glfwWindowShouldClose(window_)) {
    return true;
  }
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  return false;
}

void Display::Update() {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void Display::ResizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}