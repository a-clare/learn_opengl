#include "gl_utils.h"
#include <stdio.h>
#include <math.h>

int main() {
  GLFWwindow* win = gl_start_win("Tutorial 04 - Mats and Vecs", 640, 480);

  /* Our triangle to draw */
  GLfloat points[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
  GLfloat colors[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  GLuint points_vbo;
  GLuint colors_vbo;
  GLuint vao;

  glGenBuffers(1, &points_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glBufferData(
          /* The type of data */
          GL_ARRAY_BUFFER,
          /* The size of the data in bytes */
          9 * sizeof(GLfloat),
          /* The actual data */
          points,
          /* How we will be drawing, wont be changing the data in the buffer so its static */
          GL_STATIC_DRAW);

  glGenBuffers(1, &colors_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glBufferData(
          /* The type of data */
          GL_ARRAY_BUFFER,
          /* The size of the data in bytes */
          9 * sizeof(GLfloat),
          /* The actual data */
          colors,
          /* How we will be drawing, wont be changing the data in the buffer so its static */
          GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
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

  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glVertexAttribPointer(
          /* Attribute number */
          1,
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

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  GLuint vs = gl_load_vs_from_file("/Users/adam/Documents - Adam’s MacBook Pro/projects/learn_opengl/anton_opengl_tutorials/shaders/vs04.vs");
  GLuint fs = gl_load_fs_from_file("/Users/adam/Documents - Adam’s MacBook Pro/projects/learn_opengl/anton_opengl_tutorials/shaders/fs04.fs");

  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  GLfloat matrix[] = {
          1.0f, 0.0f, 0.0f, 0.0f, // first column
          0.0f, 1.0f, 0.0f, 0.0f, // second column
          0.0f, 0.0f, 1.0f, 0.0f, // third column
          0.5f, 0.0f, 0.0f, 1.0f  // fourth column
  };
  int matrix_location = glGetUniformLocation(program, "matrix");
  glUseProgram(program);
  glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  float speed         = 1.0f; // move at 1 unit per second
  float last_position = 0.0f;

  double previous_seconds = glfwGetTime();
  while (!glfwWindowShouldClose(win)) {
    /* Clear to white */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double current_seconds         = glfwGetTime();
    double elapsed_seconds         = current_seconds - previous_seconds;
    previous_seconds               = current_seconds;

    glUseProgram(program);

    matrix[12]    = elapsed_seconds * speed + last_position;
    last_position = matrix[12];
    if ( fabs( last_position ) > 1.0 ) {
      speed = -speed;
    }
    glUniformMatrix4fv( matrix_location, 1, GL_FALSE, matrix );

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(win);
  }
}