#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vis/Display.h"
#include "vis/ShaderLoader.h"

const char* vs_src = 
  "#version 330 core\n"
  "layout (location = 0) in vec2 coord2d;\n"
  "uniform float offset_x;\n"
  "uniform float scale_x;\n"
  "uniform lowp float sprite;\n"
  "out vec4 f_color;\n"
  "void main(void) {\n"
    "gl_Position = vec4((coord2d.x + offset_x) * scale_x, coord2d.y, 0, 1);\n"
    "f_color = vec4(coord2d.xy / 2.0 + 0.5, 1, 1);\n"
    "gl_PointSize = 10.0;\n"
  "}\n";

const char* fs_src = 
  "#version 330 core\n"
  "uniform sampler2D mytexture;\n"
  "uniform float sprite;\n"
  "in vec4 f_color;\n"
  "out vec4 FragColor;\n"
  "void main(void) {\n"
    "if (sprite > 1.0)\n"
      // "FragColor = texture2D(mytexture, gl_PointCoord) * f_color;\n"
      "FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "else\n"
      "FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
  "}\n";

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[15 * 15 * 4 + 1];
} res_texture = {
  15, 15, 4,
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\0\0\0\377\377\377\377\377\0\0\0\377\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\0"
  "\0\0\377\377\377\377\377\0\0\0\377\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\0\0\0\377\377\377"
  "\377\377\0\0\0\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\377\377\377\0\0\0\0\377\377\377\377\377\0\0"
  "\0\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\0\0\0\377\377\377\377\377\0\0\0\377\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\0\0\0\377\377\377\377\377\0\0\0\377\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\0\0\0\377"
  "\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377\377\377\377"
  "\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\377"
  "\0\0\0\377\0\0\0\377\377\377\377\377\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0"
  "\377\0\0\0\377\0\0\0\377\0\0\0\377\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\0\0\0""2\0\0\0\377\377\377\377\377\0\0\0\377"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\0\0\0\377\377\377\377\377\0\0\0\377\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\0\0\0\377\377\377\377\377\0\0\0\377\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\0\0\0\377\377"
  "\377\377\377\0\0\0\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\0\0\0\377\377\377\377\377\0"
  "\0\0\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\0\0\0\377\377\377\377\377\0\0\0\377\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0",
};

GLuint program;
GLint attribute_coord2d;
GLint uniform_offset_x;
GLint uniform_scale_x;
GLint uniform_sprite;
GLuint texture_id;
GLint uniform_mytexture;

float offset_x = 0.0;
float scale_x = 1.0;
int mode = 0;

struct point {
	GLfloat x;
	GLfloat y;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLuint vbo;
GLuint vao;

int init_resources() {
  program = LoadShaders(vs_src, fs_src);
	if (program == 0) {
		return 0;
  }

	// attribute_coord2d = glGetAttribLocation(program, "coord2d");
	uniform_offset_x = glGetUniformLocation(program, "offset_x");
	uniform_scale_x = glGetUniformLocation(program, "scale_x");
	uniform_sprite = glGetUniformLocation(program, "sprite");
	uniform_mytexture = glGetUniformLocation(program, "mytexture");

	/* Enable blending */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glGenVertexArrays(1, &vao);

	/* Upload the texture for our point sprites */
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res_texture.width, res_texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, res_texture.pixel_data);

	// Create the vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
	// Create our own temporary buffer
	point graph[2000];

	// Fill it in just like an array
	for (int i = 0; i < 2000; i++) {
		float x = (i - 1000.0) / 100.0;

		graph[i].x = x;
		graph[i].y = sin(x * 10.0) / (1.0 + x * x);
	}

	// Tell OpenGL to copy our array to the buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(graph), graph, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
	return 1;
}

void display_loop() {
  glfwPollEvents();
	glUseProgram(program);
	glUniform1i(uniform_mytexture, 0);

	glUniform1f(uniform_offset_x, offset_x);
	glUniform1f(uniform_scale_x, scale_x);

	// glClearColor(1.0, 1.0, 1.0, 1.0);
	// glClear(GL_COLOR_BUFFER_BIT);

	/* Draw using the vertices in our vertex buffer object */
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);

	// glEnableVertexAttribArray(attribute_coord2d);
	// glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);

	/* Push each element in buffer_vertices to the vertex shader */
	switch (mode) {
	case 0:
		glUniform1f(uniform_sprite, 0);
		glDrawArrays(GL_LINE_STRIP, 0, 2000);
		break;
	case 1:
		glUniform1f(uniform_sprite, 1);
		glDrawArrays(GL_POINTS, 0, 2000);
		break;
	case 2:
		glUniform1f(uniform_sprite, res_texture.width);
		glDrawArrays(GL_POINTS, 0, 2000);
		break;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
    mode = 0;
    printf("Now drawing using lines.\n");
  }
  else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
    mode = 1;
    printf("Now drawing using ponts.\n");
  }
  else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
    offset_x -= 0.1;
  }
  else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    offset_x += 0.1;
  }
  else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
    scale_x *= 1.5;
  }
  else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    scale_x /= 1.5;
  }
}

void free_resources() {
	glDeleteProgram(program);
}

int main(int argc, char *argv[]) {
	
  Display display("Simple Graph", 800, 600);
  
  glfwSetKeyCallback(display.GetWindow(), key_callback);
  display.SetClearColor(1.0, 1.0, 1.0, 1.0);
	printf("Use left/right to move horizontally.\n");
	printf("Use up/down to change the horizontal scale.\n");
	printf("Press home to reset the position and scale.\n");
	printf("Press F1 to draw lines.\n");
	printf("Press F2 to draw points.\n");
	printf("Press F3 to draw point sprites.\n");

  init_resources();

  while(!display.Shutdown()) {

    // Process input
    display_loop();
    display.Update();
  }

	free_resources();
	return 0;
}
