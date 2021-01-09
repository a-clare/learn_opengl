#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vis/Display.h"
#include "vis/ShaderLoader.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vs_src = 
  "#version 330 core\n"
  "layout (location = 0) in vec2 coord2d;\n"
  "uniform mat4 transform;\n"
  "void main(void) {\n"
    "gl_Position = transform * vec4(coord2d.xy, 0, 1);\n"
  "}\n";

const char* fs_src = 
  "#version 330 core\n"
  "uniform vec4 color;\n"
  "out vec4 FragColor;\n"
  "void main(void) {\n"
      "FragColor = color;\n"
  "}\n";

GLuint program;
GLint attribute_coord2d;
GLint uniform_color;
GLint uniform_transform;

float offset_x = 0;
float scale_x = 1;

struct point {
	GLfloat x;
	GLfloat y;
};

GLuint vbo[3];
GLuint vao;

const int border = 10;
const int ticksize = 10;

Display display("Simple Graph", 800, 600);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int init_resources() {
	program = LoadShaders(vs_src, fs_src);
	if (program == 0)
		return 0;

  attribute_coord2d = glGetAttribLocation(program, "coord2d");
	uniform_transform = glGetUniformLocation(program, "transform");
	uniform_color = glGetUniformLocation(program, "color");

	// Create the vertex buffer object
  glGenVertexArrays(1, &vao);
	glGenBuffers(3, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof graph, graph, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

	// Create a VBO for the border
	static const point border[4] = { {-1, -1}, {1, -1}, {1, 1}, {-1, 1} };
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof border, border, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
	return 1;
}

// Create a projection matrix that has the same effect as glViewport().
// Optionally return scaling factors to easily convert normalized device coordinates to pixels.
//
glm::mat4 viewport_transform(float x, float y, float width, float height, float *pixel_x = 0, float *pixel_y = 0) {
	// Map OpenGL coordinates (-1,-1) to window coordinates (x,y),
	// (1,1) to (x + width, y + height).

	// First, we need to know the real window size:
	int window_width;
	int window_height;
  glfwGetWindowSize(display.GetWindow(), &window_width, &window_height);
  // window_height *= 2;
  // window_width *= 2;
	// Calculate how to translate the x and y coordinates:
	float offset_x = (2.0 * x + (width - window_width)) / window_width;
	float offset_y = (2.0 * y + (height - window_height)) / window_height;

	// Calculate how to rescale the x and y coordinates:
	float scale_x = width / window_width;
	float scale_y = height / window_height;

	// Calculate size of pixels in OpenGL coordinates
	if (pixel_x)
		*pixel_x = 2.0 / width;
	if (pixel_y)
		*pixel_y = 2.0 / height;

	return glm::scale(glm::translate(glm::mat4(1), glm::vec3(offset_x, offset_y, 0)), glm::vec3(scale_x, scale_y, 1));
}

void display_loop() {
  glfwPollEvents();
	int window_width;
	int window_height;
  glfwGetWindowSize(display.GetWindow(), &window_width, &window_height);
  // window_height *= 2;
  // window_width *= 2;
	glUseProgram(program);

	/* ---------------------------------------------------------------- */
	/* Draw the graph */

	// Set our viewport, this will clip geometry
	glViewport(border + ticksize, border + ticksize, window_width - border * 2 - ticksize, window_height - border * 2 - ticksize);

	// Set the scissor rectangle,this will clip fragments
	glScissor(border + ticksize, border + ticksize, window_width - border * 2 - ticksize, window_height - border * 2 - ticksize);

	glEnable(GL_SCISSOR_TEST);

	// Set our coordinate transformation matrix
	glm::mat4 transform = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(scale_x, 1, 1)), glm::vec3(offset_x, 0, 0));
	glUniformMatrix4fv(uniform_transform, 1, GL_FALSE, glm::value_ptr(transform));

	// Set the color to red
	GLfloat red[4] = { 1, 0, 0, 1 };
	glUniform4fv(uniform_color, 1, red);

	// Draw using the vertices in our vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glEnableVertexAttribArray(attribute_coord2d);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_LINE_STRIP, 0, 2000);

	// Stop clipping
	glViewport(0, 0, window_width, window_height);
	glDisable(GL_SCISSOR_TEST);

	/* ---------------------------------------------------------------- */
	/* Draw the borders */

	float pixel_x, pixel_y;

	// Calculate a transformation matrix that gives us the same normalized device coordinates as above
	transform = viewport_transform(border + ticksize, border + ticksize, window_width - border * 2 - ticksize, window_height - border * 2 - ticksize, &pixel_x, &pixel_y);

	// Tell our vertex shader about it
	glUniformMatrix4fv(uniform_transform, 1, GL_FALSE, glm::value_ptr(transform));

	// Set the color to black
	GLfloat black[4] = { 0, 0, 0, 1 };
	glUniform4fv(uniform_color, 1, black);

	// Draw a border around our graph
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	/* ---------------------------------------------------------------- */
	/* Draw the y tick marks */

	point ticks[42];

	for (int i = 0; i <= 20; i++) {
		float y = -1 + i * 0.1;
		float tickscale = (i % 10) ? 0.5 : 1;

		ticks[i * 2].x = -1;
		ticks[i * 2].y = y;
		ticks[i * 2 + 1].x = -1 - ticksize * tickscale * pixel_x;
		ticks[i * 2 + 1].y = y;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof ticks, ticks, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 42);

	/* ---------------------------------------------------------------- */
	/* Draw the x tick marks */

	float tickspacing = 0.1 * powf(10, -floor(log10(scale_x)));	// desired space between ticks, in graph coordinates
	float left = -1.0 / scale_x - offset_x;	// left edge, in graph coordinates
	float right = 1.0 / scale_x - offset_x;	// right edge, in graph coordinates
	int left_i = ceil(left / tickspacing);	// index of left tick, counted from the origin
	int right_i = floor(right / tickspacing);	// index of right tick, counted from the origin
	float rem = left_i * tickspacing - left;	// space between left edge of graph and the first tick

	float firsttick = -1.0 + rem * scale_x;	// first tick in device coordinates

	int nticks = right_i - left_i + 1;	// number of ticks to show

	if (nticks > 21)
		nticks = 21;	// should not happen

	for (int i = 0; i < nticks; i++) {
		float x = firsttick + i * tickspacing * scale_x;
		float tickscale = ((i + left_i) % 10) ? 0.5 : 1;

		ticks[i * 2].x = x;
		ticks[i * 2].y = -1;
		ticks[i * 2 + 1].x = x;
		ticks[i * 2 + 1].y = -1 - ticksize * tickscale * pixel_y;
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof ticks, ticks, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, nticks * 2);

	// And we are done.
	// glDisableVertexAttribArray(attribute_coord2d);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		offset_x -= 0.03;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		offset_x += 0.03;
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		scale_x *= 1.5;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		scale_x /= 1.5;
}

void free_resources() {
	glDeleteProgram(program);
}

int main(int argc, char *argv[]) {
  
  glfwSetKeyCallback(display.GetWindow(), key_callback);
  display.SetClearColor(1.0, 1.0, 1.0, 1.0);
  init_resources();
	while(!display.Shutdown()) {
    // Process input
    display_loop();
    display.Update();
  }

	free_resources();
	return 0;
}
