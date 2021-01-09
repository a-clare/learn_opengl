#include "vis/Display.h"
#include "vis/Logger.h"

Display::Display(const std::string& windowName, std::uint16_t width, std::uint16_t height) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window_ = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
  if (window_ == NULL) {
    LOG_ERROR << "Failed to create window";
    return;
  }
  LOG_INFO << "Created window of size " << width << "x" << height;
  glfwMakeContextCurrent(window_);
  glfwSetFramebufferSizeCallback(window_, &Display::ResizeCallback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    /* TODO: What to do on failure, probably throw an exception of some sort? */
    return;
  }
  /* Set default background clear color to white */
  clear_color_[0] = 1.0;
  clear_color_[1] = 1.0;
  clear_color_[2] = 1.0;
  clear_color_[3] = 1.0;
}

bool Display::Shutdown() const {
  if(glfwWindowShouldClose(window_)) {
    return true;
  }
  glClearColor(clear_color_[0], clear_color_[1], clear_color_[2], clear_color_[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  return false;
}

void Display::Update() {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void Display::SetClearColor(float r, float g, float b, float a) {
  clear_color_[0] = r;
  clear_color_[1] = g;
  clear_color_[2] = b;
  clear_color_[3] = a;
}

GLFWwindow* Display::GetWindow(){
  return window_;
}

void Display::GetWindowSize(int& width, int& height) {
  glfwGetWindowSize(window_, &width, &height);
}

void Display::ResizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}