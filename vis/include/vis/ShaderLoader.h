#ifndef __VIS_SHADER_LOADER_H__
#define __VIS_SHADER_LOADER_H__

#include <fstream>

/* 
  Load a vertex and fragment shader from a file.
  Expects the input file to be full path
  Returns an OpenGL shader program index (0 on failure)
 */
unsigned int LoadShadersFromFile(
  const std::string& vertexShaderFile, const std::string& fragShaderFile);

/* 
  Load a vertex and fragment shader source programs
  Returns an OpenGL shader program index (0 on failure)
 */
unsigned int LoadShaders(const char* vertexShaderSrc, const char* fragShaderSrc);


#endif