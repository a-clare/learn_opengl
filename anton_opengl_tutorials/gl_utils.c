#include "gl_utils.h"
#include <stdio.h>

GLFWwindow* gl_start_win(const char* winName, int w, int h) {
  GLFWwindow* ret_win;
  printf("Starting GLFW %s\n", glfwGetVersionString());
  if (!glfwInit()) {
    printf("Error: Could not start GLFW\n");
    return NULL;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  ret_win = glfwCreateWindow(w, h, winName, NULL, NULL);
  if (ret_win == NULL) {
    printf("Error: Could not open window\n");
  }
  glfwMakeContextCurrent(ret_win);
  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Error: Could not initialize GLAD");
    return 0;
  }

  printf("Renderer %s\n", glGetString(GL_RENDERER));
  printf("Version %s\n", glGetString(GL_VERSION));

  return ret_win;
}

GLuint gl_load_vs_from_file(const char* fn) {
  printf("Loading vertex shader %s\n", fn);
  FILE* f = fopen(fn, "r");
  if (!f) {
    printf("Could not open file %s\n", fn);
    return 0;
  }
  /* Buffer for reading in data from file */
  char buf[2048];
  /* Reading data into buf, size 1 byte, and read 2047 of them. We read 2047 to
    make sure we have a null terminated string */
  size_t cnt = fread(buf, 1, 2047, f);
  printf("Read %lu bytes \n", cnt);
  printf("Src\n%s\n", buf);
  buf[cnt] = '\0';
  fclose(f);

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  /* Setting source of shader vs, there is 1 shader in the source, and NULL 
    for the length since we null terminated our string. Casting from char*
    to remove compile warnings about different types */
  const GLchar* p = (const GLchar*)buf;
  glShaderSource(vs, 1, &p, NULL);
  glCompileShader(vs);

  /* Check for compile errors */
  int success = -1;
  char info_log[512];
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vs, 512, NULL, info_log);
    printf("Error in compiling shader. \n%s\n", info_log);
    return 0;
  }

  return vs;
}

GLuint gl_load_fs_from_file(const char* fn) {
  printf("Loading fragment shader %s\n", fn);
  FILE* f = fopen(fn, "r");
  if (!f) {
    printf("Could not open file %s\n", fn);
    return 0;
  }
  /* Buffer for reading in data from file */
  char buf[2048];
  /* Reading data into buf, size 1 byte, and read 2047 of them. We read 2047 to
    make sure we have a null terminated string */
  size_t cnt = fread(buf, 1, 2047, f);
  printf("Read %lu bytes \n", cnt);
  printf("Src\n%s\n", buf);
  buf[cnt] = '\0';
  fclose(f);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  /* Setting source of shader vs, there is 1 shader in the source, and NULL 
    for the length since we null terminated our string. Casting from char*
    to remove compile warnings about different types */
  const GLchar* p = (const GLchar*)buf;
  glShaderSource(fs, 1, &p, NULL);
  glCompileShader(fs);

  /* Check for compile errors */
  int success = -1;
  char info_log[512];
  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fs, 512, NULL, info_log);
    printf("Error in compiling shader. \n%s\n", info_log);
    return 0;
  }

  return fs;
}