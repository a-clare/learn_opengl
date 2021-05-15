#ifndef __GL_UTILS_H__
#define __GL_UTILS_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* Start an open GL context with a window name, and size (w x h) 
  Returns 0 if there is an error */
GLFWwindow* gl_start_win(const char* winName, int w, int h);

/* Load a vertex shader from a file. Will attempt to compile shader on load */
GLuint gl_load_vs_from_file(const char* fn);

#endif