#include "vis/Display.h"
#include "vis/ShaderLoader.h"
#include <iostream>
#include <cmath>

/* Callback anytime a key is pressed */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
/* Vertex shader source */
static const char* vs_src = {
  "#version 400 core                                                 \n"
  "layout (location = 0) in vec4 offset;                             \n"
  "layout (location = 1) in vec4 color;                              \n"
  "out vec4 vs_color;                                                \n"
  "void main(void)                                                   \n"
  "{                                                                 \n"
  "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
  "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
  "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
  "                                                                  \n"
  "    gl_Position = vertices[gl_VertexID] + offset;                 \n"
  "    vs_color = color;                                             \n"
  "}                                             \n"
};

/* Fragment shader source */
static const char* fs_src = {
    "#version 400 core                             \n"
    "in vec4 vs_color;                             \n"
    "out vec4 color;                               \n"
    "void main(void)                               \n"
    "{                                             \n"
    "    color = vs_color;                         \n"
    "}                                             \n"
};

int mode = 1;

/*
  This is a modified example of drawing an animated triangle tutorial in 
  the OpenGL Super Bible, listing 3.1 and 3.2
*/
int main() {
  /* Setup window and callback for user input */
  Display display("Animated Triangle", 800, 600);
  std::cout << "Display a single triangle" << std::endl;
  display.SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glfwSetKeyCallback(display.GetWindow(), key_callback);

  /* Load shaders and create a shader program */
  unsigned int program = LoadShaders(vs_src, fs_src);
  /* In core OpenGL we require a vertex array object (vao) in order to draw anything */
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  while (!display.Shutdown()) {
    /* Drawing of our single triangle */
    glUseProgram(program);
    float attrib[4] = {
      std::sin(glfwGetTime()) * 0.5f,
      std::cos(glfwGetTime()) * 0.6f,
      0.0f, 0.0f};
    glVertexAttrib4fv(0, attrib);

    if (mode == 1) {
      float color[4] = {0.0f, 0.8f, 1.0f, 1.0f};
      glVertexAttrib4fv(1, color);
    }
    if (mode == 2) {
      float color[4] = {
        0.0f,
        std::sin(glfwGetTime()) * 0.5f + 0.5f,
        std::cos(glfwGetTime()) * 0.5f + 0.5f,
        1.0f};
      glVertexAttrib4fv(1, color);
    }
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
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
}