#include "vis/Display.h"
#include <iostream>

int main() {
  Display Display(" ", 1, 1);
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}