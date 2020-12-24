#include "vis/Display.h"
#include <iostream>

int main() {
  Display display("Hello window", 800, 600);
  while (!display.Shutdown()) {
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    display.Update();
  }
}