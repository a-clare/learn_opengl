#include "vis/Display.h"
#include "vis/ShaderLoader.h"
#include <iostream>
#include <cmath>

/* Callback anytime a key is pressed */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
/* Current size of the point to display */
float pt_size = 1.0f;

/* Vertex shader source */
static const char* vs_src = {
  "#version 400 core                             \n"
  "void main(void)                               \n"
  "{                                             \n"
  "    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);   \n"
  "}                                             \n"
};

/* Fragment shader source */
static const char* fs_src = {
    "#version 400 core                             \n"
    "out vec4 color;                               \n"
    "void main(void)                               \n"
    "{                                             \n"
    "    color = vec4(0.0, 0.8, 1.0, 1.0);         \n"
    "}                                             \n"
};

/*
  This is a modified example of drawing a single point tutorial in 
  the OpenGL Super Bible, listing 2.2 and 2.3
*/
int main() {
  /* Setup window and callback for user input */
  Display display("Single Point", 800, 600);
  std::cout << "Display a single point and change the size: \n" <<
    "\t Up == increase size\n" << 
    "\t Down == decrease size" << std::endl;
  glfwSetKeyCallback(display.GetWindow(), key_callback);
  display.SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);

  /* Load shaders and create a shader program */
  unsigned int program = LoadShaders(vs_src, fs_src);
  /* In core OpenGL we require a vertex array object (vao) in order to draw anything */
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  while (!display.Shutdown()) {
    /* Drawing of our single point */
    glUseProgram(program);
    glPointSize(pt_size);
    glDrawArrays(GL_POINTS, 0, 1);

    display.Update();
  }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
    pt_size += 8.0f;
    if (pt_size > 64.0f) {
      pt_size = 64.0f;
    }
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    pt_size -= 8.0f;
    if (pt_size < 1.0f) {
      pt_size = 1.0f;
    }
  }
}