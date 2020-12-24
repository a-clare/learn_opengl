#ifndef __VIS_DISPLAY_H__
#define __VIS_DISPLAY_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cstdint>

/* 
  Simple class for managing the GL window that user will interact with and 
  items will be drawn to.
  To use a display object:
  Display my_display("my name", 800, 600)
  ...
  while (!my_display.Shutdown()) {
    // do stuff/draw

    my_display.Update();
  }
*/
class Display {
public:
  Display(const std::string& windowName, std::uint16_t width, std::uint16_t height);

  /* Returns true if the window is shut/closed */
  bool Shutdown() const;

  /* Update the GL context, clear screen, swap buffers, etc */
  void Update();
  
  /* Set the clear color on re-draws. (0 to 1 input) */
  void SetClearColor(float r, float g, float b, float a);

  /* Return the window instance */
  GLFWwindow* GetWindow();
private:

  static void ResizeCallback(GLFWwindow* window, int width, int height);
  
  GLFWwindow* window_;

  float clear_color_[4];
};

#endif