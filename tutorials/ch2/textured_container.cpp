#define STB_IMAGE_IMPLEMENTATION
#include "vis/stb_image.h"

#include "vis/Display.h"
#include "vis/ShaderLoader.h"
#include <iostream>

const char *vs_src = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  "layout (location = 3) in vec2 aTexCoord;\n"
  "out vec3 outColor;\n"
  "out vec2 TexCoord;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "   outColor = aColor;\n"
  "   TexCoord = aTexCoord;\n"
  "}\0";
  
const char *fs_src = "#version 330 core\n"
  "in vec3 outColor;\n"
  "out vec3 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = outColor;\n"
  "}\n\0";


int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "No input path provided for container.jpg" << std::endl;
    std::cout << "Usage would be something like \n ./build/texured_container.cpp /res/container.jpg"
      << std::endl;
    return 0;
  }
  /* Load the image */
  int image_width, image_height, image_channels;
  unsigned char* image = stbi_load(argv[1], &image_width, &image_height, &image_channels, 0);
  
  Display display("Simple Triangle", 800, 600);
  /* Coordinates of the triangle corners in NDC (normalized device coordinates) */
  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,  0.75f, 0.0f, 0.0f, 0.0f, 1.0f};

  /* 
    Vertex buffer object (VBO) 
    We are allocating memory (buffer) on the GPU that we can then index
    or reference by using the vbo int value 
  */
  unsigned int vbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  /* This sends the vertices data to the GPU. */
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
  static const int size_float = sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * size_float, (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * size_float, (void*)(3 * size_float));
  glEnableVertexAttribArray(1);

  unsigned int shader_program = LoadShaders(vs_src, fs_src);

  while (!display.Shutdown()) {
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    display.Update();
  }
}