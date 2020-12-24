#include "vis/Display.h"
#include "vis/ShaderLoader.h"
#include <iostream>

const char *vs_src = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";
  
const char *fs_src = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n\0";

/* Process user input */
static void ProcessInput(GLFWwindow* window);
static bool show_line_mode = false;

/* 
  Display a rectangle to the screen
  Can press 'w' to show lines or fill mode 
*/
int main() {
  Display display("Simple Rectangle Using Indices", 800, 600);
  /* Coordinates of the rectangle corners in NDC (normalized device coordinates) */
  float vertices[] = {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f};
  /* 
    The indicies/order of vertex positions (in vertices[] above) we want to draw.
    So we want to draw V0, V1, V3 to create the first triangle, then draw
    V1 V2 V3 to get the second triangle, which will form a rectangle
  */
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3};
  /* 
    Vertex buffer object (VBO) 
    We are allocating memory (buffer) on the GPU that we can then index
    or reference by using the vbo int value 
    EBO (Element buffer object) is used for drawing based off indicies
  */
  unsigned int vbo, vao, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  /* This sends the vertices data to the GPU. */
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  /* 
    Tells the GPU how to use vertices[]. 
    0 is the layout location (for use in the shader)  
    3 the number of components in the vertex attribute (x y z coordinates)
    GL_FLOAT type
    GL_FALSE because the inputs are already normalized (-1 to 1)
    12 (3 * 4 bytes for a float) stride. This is how many bytes until the next attribute in the buffer
    0 because we are starting at the front of the buffer

    NOTE: notice the first 0 (layout) is the same value as the layout value in the 
    vertex shader source at the top of the program
  */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  unsigned int shader_program = LoadShaders(vs_src, fs_src);

  while (!display.Shutdown()) {
    ProcessInput(display.GetWindow());
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    display.Update();
  }
}

static void ProcessInput(GLFWwindow* window) {
  /* User has hit the esc key */
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    if (show_line_mode) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    show_line_mode = !show_line_mode;
  }
}