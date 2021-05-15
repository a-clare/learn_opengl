#include "gl_utils.h"
#include <stdio.h>
#include <math.h>

int main() {
  GLFWwindow* win = gl_start_win("Tutorial 02 - Shaders", 640, 480);

  /* Our triangle to draw */
  GLfloat points[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
  
  GLuint vbo;
  GLuint vao;

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(
    /* The type of data */ 
    GL_ARRAY_BUFFER, 
    /* The size of the data in bytes */
    9 * sizeof(GLfloat),
    /* The actual data */
    points, 
    /* How we will be drawing, wont be changing the data in the buffer so its static */
    GL_STATIC_DRAW);
  
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  /* Technically buffer already binded but good practice */
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(
    /* Attribute number */
    0, 
    /* Number of variables in one attribute (X/Y/Z) */
    3, 
    /* Type of variable */
    GL_FLOAT, 
    /* Flag indicating if we need to normalize data */
    GL_FALSE,
    /* Stride, 0 indicating bytes are tightly packed */ 
    0,
    /* Offset pointer */
    NULL);

  GLuint vs = gl_load_vs_from_file("/Users/adam/Documents - Adam’s MacBook Pro/projects/learn_opengl/anton_opengl_tutorials/shaders/vs02.vs");
  GLuint fs = gl_load_fs_from_file("/Users/adam/Documents - Adam’s MacBook Pro/projects/learn_opengl/anton_opengl_tutorials/shaders/fs02.fs");
  
  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  GLuint uniform_color_loc = glGetUniformLocation(program, "inputColour");
  glUseProgram(program);
  glUniform4f(uniform_color_loc, 1.0f, 0.0f, 0.0f, 1.0f );

  while (!glfwWindowShouldClose(win)) {
    /* Clear to white */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Change the color of the triangle by updating the uniform */
    float timeValue = glfwGetTime();
    float g = sin(timeValue) / 2.0f + 0.5f;
    float r = cos(timeValue) / 2.0f;
    glUniform4f(uniform_color_loc, r, g, 0.0f, 1.0f);

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(win);
  }
}