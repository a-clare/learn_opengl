#include "vis/Display.h"
#include <iostream>
#include <cmath>

/* Callback anytime a key is pressed */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
/* What mode we are in, 0 is red, 1 is green, 2 is blue, 3 is time changing color */
int mode = 0;

/*
  This is a modified example of the simple window/clear tutorial in 
  the OpenGL Super Bible, listing 2.1 and 2.2.
*/
int main() {
  Display display("Simple Window", 200, 100);
  std::cout << "Display a single window and change the color: \n" <<
    "\t 1 == red\n" << 
    "\t 2 == green\n" <<
    "\t 3 == blue\n" << 
    "\t 4 == alternating" << std::endl;
  glfwSetKeyCallback(display.GetWindow(), key_callback);

  /* Default clear to a white background */
  float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  while (!display.Shutdown()) {
    /* Red background */
    if (mode == 1) {
      color[0] = 1.0f;
      color[1] = 0.0f;
      color[2] = 0.0f;
      color[3] = 1.0f;
    }
    /* Green */
    if (mode == 2) {
      color[0] = 0.0f;
      color[1] = 1.0f;
      color[2] = 0.0f;
      color[3] = 1.0f;
    }
    /* Blue */
    if (mode == 3) {
      color[0] = 0.0f;
      color[1] = 0.0f;
      color[2] = 1.0f;
      color[3] = 1.0f;
    }
    /* Alternating */
    if (mode == 4) {
      color[0] = std::sin(glfwGetTime()) * 0.5f + 0.5f;
      color[1] = std::cos(glfwGetTime()) * 0.5f + 0.5f;
      color[2] = 0.0f;
      color[3] = 1.0f;
    }
    glClearBufferfv(GL_COLOR, 0, color);
    display.Update();
  }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
    mode = 1;
  }
  if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
    mode = 2;
  }
  if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
    mode = 3;
  }
  if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
    mode = 4;
  }
}