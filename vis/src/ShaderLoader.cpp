#include "vis/ShaderLoader.h"
#include <glad/glad.h>
#include <sstream>
#include <iostream>

unsigned int LoadShadersFromFile(
  const std::string& vertexShaderFile, const std::string& fragShaderFile) {
  std::ifstream vs_file;
  std::ifstream fs_file;
  std::string vs_src, fs_src;
  try {
    vs_file.open(vertexShaderFile);
    fs_file.open(fragShaderFile);
    std::stringstream vs_stream, fs_stream;
    vs_stream << vs_file.rdbuf();
    fs_stream << fs_file.rdbuf();
    vs_file.close();
    fs_file.close();
    vs_src = vs_stream.str();
    fs_src = fs_stream.str();			
  }
  catch (std::ifstream::failure& e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  return LoadShaders(vs_src.c_str(), fs_src.c_str());
}

unsigned int LoadShaders(const char* vertexShaderSrc, const char* fragShaderSrc) {
  unsigned int vs, fs;
  unsigned int program;
  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertexShaderSrc, NULL);
  glCompileShader(vs);
  int success;
  char info_log[512];
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vs, 512, NULL, info_log);
    std::cout << "Vertex shader compilation failed\n" << info_log << std::endl;
    return 0;
  }

  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragShaderSrc, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fs, 512, NULL, info_log);
    std::cout << "Fragment shader compilation failed\n" << info_log << std::endl;
    return 0;
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, info_log);
    std::cout << "Program compilation failed\n " << info_log << std::endl;
    return 0;
  }
  /* Dont need the shaders anymore once loaded onto the GPU */
  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
}