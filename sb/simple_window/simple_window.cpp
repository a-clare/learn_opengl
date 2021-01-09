#include "vis/Display.h"

int main() {
  Display display("Simple Window", 200, 100);
  while (!display.Shutdown()) {
    // Simply clear the window with red
    static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, red);
    
    display.Update();
  }
}