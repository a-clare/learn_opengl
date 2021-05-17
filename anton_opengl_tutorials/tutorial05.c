#include "gl_utils.h"
#include "math_utils.h"
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

  GLuint vs = gl_load_vs_from_file("/Users/adam/Documents - Adam’s MacBook Pro/projects/learn_opengl/anton_opengl_tutorials/shaders/vs05.vs");
  GLuint fs = gl_load_fs_from_file("/Users/adam/Documents - Adam’s MacBook Pro/projects/learn_opengl/anton_opengl_tutorials/shaders/fs05.fs");

  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  /*--------------------------create camera matrices----------------------------*/
  /* create PROJECTION MATRIX */
  // input variables
  float near   = 0.1f;                                   // clipping plane
  float far    = 100.0f;                                 // clipping plane
  float fov    = 67.0f * ONE_DEG_IN_RAD;                 // convert 67 degrees to radians
  float aspect = (float)640 / (float)480.0; // aspect ratio
  // matrix components
  float inverse_range = 1.0f / tan( fov * 0.5f );
  float Sx            = inverse_range / aspect;
  float Sy            = inverse_range;
  float Sz            = -( far + near ) / ( far - near );
  float Pz            = -( 2.0f * far * near ) / ( far - near );
  GLfloat proj_mat[]  = { Sx, 0.0f, 0.0f, 0.0f, 0.0f, Sy, 0.0f, 0.0f, 0.0f, 0.0f, Sz, -1.0f, 0.0f, 0.0f, Pz, 0.0f };

  /* create VIEW MATRIX */
  float cam_speed     = 1.0f;                 // 1 unit per second
  float cam_yaw_speed = 10.0f;                // 10 degrees per second
  float cam_yaw       = 0.0f;                 // y-rotation in degrees

  mat4 I = mat4_identity();
  vec3 cam_pos;
  cam_pos.v[0] = 0.0f;
  cam_pos.v[1] = 0.0f;
  cam_pos.v[2] = 2.0f;
  mat4 T = mat4_translate(&I, &cam_pos);

  mat4 R              = rotate_y_deg( identity_mat4(), -cam_yaw );
  mat4 view_mat       = R * T;

  /* get location numbers of matrices in shader programme */
  GLint view_mat_location = glGetUniformLocation(program, "view" );
  GLint proj_mat_location = glGetUniformLocation(program, "proj" );

  glUseProgram(program);
  glUniformMatrix4fv( view_mat_location, 1, GL_FALSE, view_mat.m );
  glUniformMatrix4fv( proj_mat_location, 1, GL_FALSE, proj_mat );

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  double previous_seconds = glfwGetTime();
  while (!glfwWindowShouldClose(win)) {
    /* Clear to white */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double current_seconds         = glfwGetTime();
    double elapsed_seconds         = current_seconds - previous_seconds;
    previous_seconds               = current_seconds;

    glUseProgram(program);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(win);
  }
}