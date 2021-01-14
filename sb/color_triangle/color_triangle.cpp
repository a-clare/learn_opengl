#include "vis/Display.h"
#include "vis/ShaderLoader.h"
#include <iostream>
#include <cmath>

/* Callback anytime a key is pressed */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
/* Vertex shader source */
static const char* vs_src = {
  "#version 400 core                                                 \n"
  "layout (location = 0) in vec3 vertices;                             \n"
  "layout (location = 1) in vec3 color;                              \n"
  "out vec4 vs_color;                                                \n"
  "void main(void)                                                   \n"
  "{                                                                 \n"
  "    gl_Position = vec4(vertices, 1.0);                 \n"
  "    vs_color = vec4(color, 1.0);                                             \n"
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
  Create a colorful triangle using vertex buffers 
  Modified example from Super bible listing 5.7
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
  unsigned int buffers[2];

  /* The actual data of our vertices and colors for each vertex */
  static const float positions[] = {
    0.25f, -0.25f, 0.5f,
    -0.25f, -0.25f, 0.5f,
    0.25f,  0.25f, 0.5f};
  static const float colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f};

  glCreateVertexArrays(1, &vao);
  glCreateBuffers(2, buffers);

  // Initialize the first buffer, for position data
  glNamedBufferStorage(buffers[0], sizeof(positions), positions, 0);
  // Bind the buffer to the vertex array
  glVertexArrayVertexBuffer(vao, 0, buffers[0], 0, 3 * sizeof(float));
  // Tell opengl that the buffer is type float
  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vao, 0, 0);
  glEnableVertexArrayAttrib(vao, 0);
  
  glNamedBufferStorage(buffers[1], sizeof(colors), colors, 0);
  glVertexArrayVertexBuffer(vao, 1, buffers[1], 0, 3 * sizeof(float));
  glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vao, 1, 1);
  glEnableVertexArrayAttrib(vao, 1);
  while (!display.Shutdown()) {
    /* Drawing of our single triangle */
    glUseProgram(program);

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