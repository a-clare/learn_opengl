#define STB_IMAGE_IMPLEMENTATION
#include "vis/stb_image.h"

#include "vis/Display.h"
#include "vis/ShaderLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

const char *vs_src = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  "layout (location = 2) in vec2 aTexCoord;\n"
  "uniform mat4 transform;\n"
  "out vec3 outColor;\n"
  "out vec2 TexCoord;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "   outColor = aColor;\n"
  "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
  "}\0";
  
const char *fs_src = "#version 330 core\n"
  "in vec3 outColor;\n"
  "in vec2 TexCoord;\n"
  "out vec4 FragColor;\n"
  "uniform sampler2D texture1;\n"
  "uniform int useColor;\n"
  "void main()\n"
  "{\n"
  "   if (useColor == 1)\n"
  "     FragColor = texture(texture1, TexCoord) * vec4(outColor, 1);\n"
  "   else\n"
  "     FragColor = texture(texture1, TexCoord);\n"
  "}\n\0";

int use_color;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char* argv[]) {
  std::cout << "Press 1 to toggle color" << std::endl;
  if (argc < 2) {
    std::cout << "No input path provided for container.jpg" << std::endl;
    std::cout << "Usage would be something like \n ./build/texured_container.cpp /res/container.jpg"
      << std::endl;
    return 0;
  }
  /* Load the image */
  int image_width, image_height, image_channels;
  unsigned char* image = stbi_load(argv[1], &image_width, &image_height, &image_channels, 0);
  if (!image) {
    std::cout << "Could not load " << argv[1] << std::endl;
    return 0;
  }
  Display display("Transformations", 800, 600);
  /* First three columns are the NDC (normalized device coordinates) of where
    the image will appear on the screen. 
    Next 3 columns are the colors for each vertex
    Last 2 columns are the coordinates of the texture (sometimes called UV coordinates).
    These are where we sample the texture from, and by using 0 to 1, we are saying sample
    the whole image */
  float vertices[] = {
      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };
  /* Indicies in vertices[] on the two triangles we are going to create */
  unsigned int indices[] = {0, 1, 3, 1, 2, 3};
  /* 
    Vertex buffer object (VBO) 
    We are allocating memory (buffer) on the GPU that we can then index
    or reference by using the vbo int value 
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
  static const int size_float = sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8* size_float, (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * size_float, (void*)(3 * size_float));
  glEnableVertexAttribArray(1);
  /* Setting the attribute for the texture in vertices[] (aTextCoord in the shader) */
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * size_float, (void*)(6 * size_float));
  glEnableVertexAttribArray(2);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  /* Set the wrapping filtering options to the currently boud texture */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  /* This sends the image data over to the currently bound image texture */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  /* Since we arent modifying the image we can free it now that its been sent over to the gpu */
  stbi_image_free(image);
  glGenerateMipmap(GL_TEXTURE_2D);

  unsigned int shader_program = LoadShaders(vs_src, fs_src);
  int use_color_idx = glGetUniformLocation(shader_program, "useColor");
  glfwSetKeyCallback(display.GetWindow(), key_callback);
  while (!display.Shutdown()) {
    glUniform1i(use_color_idx, use_color);
    /* Create the transformation */
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    /* Rotating around the Z axis, which is the axis out of the screen */
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    glUseProgram(shader_program);
    
    /* Set the uniform in the shader to use the new transformation matrix */
    unsigned int transform_loc = glGetUniformLocation(shader_program, "transform");
    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    display.Update();
  }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
    if (use_color) {
      use_color = 0;
    }
    else {
      use_color = 1;
    }
  }
}