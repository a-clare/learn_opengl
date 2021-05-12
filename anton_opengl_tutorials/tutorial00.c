#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
  /* The main window/opengl context */
  GLFWwindow* window = NULL;
  /* String from opengl providing renderer and version information */
  const GLubyte* renderer;
  const GLubyte* version;
  /* Vertex array object */
  GLuint vao;
  /* Vertex buffer object */
  GLuint vbo;

  /* The points or vertices of our triangle we are going to draw 
    X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3 
    Since its 2D all Z's == 0*/
  GLfloat points[] = { 
    0.0f, 0.5f, 0.0f, 
    0.5f, -0.5f, 0.0f, 
    -0.5f, -0.5f, 0.0f };
  
  /* Vertex shader (VS) source */
  const char* vs_src =
    "#version 410\n"
    "in vec3 vp;"
    "void main () {"
    "  gl_Position = vec4(vp, 1.0);"
    "}";

  /* Fragment shader (FS) source */
  const char* fs_src =
    "#version 410\n"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
    "}";

  /* GL shader objects for vertex and fragment shader [components] */
  GLuint vs, fs;
  /* GL shader programme object [combined, to link] */
  GLuint program;

  /* start GL context and O/S window using the GLFW helper library */
  if ( !glfwInit() ) {
    fprintf( stderr, "ERROR: could not start GLFW3\n" );
    return 1;
  }

  /* Version 4.1 Core is a good default that should run on just about everything. Adjust later to suit project requirements. */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL );
  if ( !window ) {
    fprintf( stderr, "ERROR: could not open window with GLFW3\n" );
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("ERROR: Could not initialize GLAD");
    return 1;
  }

  renderer = glGetString(GL_RENDERER); /* get renderer string */
  version  = glGetString(GL_VERSION);  /* version as a string */
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  /* tell GL to only draw onto a pixel if the shape is closer to the viewer
  than anything already drawn at that pixel */
  glEnable( GL_DEPTH_TEST ); /* enable depth-testing */
  /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
  glDepthFunc( GL_LESS );

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(
    /* The type of data */ 
    GL_ARRAY_BUFFER, 
    /* The size of the data in bytes */
    9 * sizeof(GLfloat),
    /* The actual data */
    points, 
    /* How we will be drawing, wont be changing the data in the buffer so its static */
    GL_STATIC_DRAW);
  
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  /* Technically buffer already binded but good practice */
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(
    /* Attribute number */
    0, 
    /* Number of variables in one attribute (X/Y/Z) */
    3, 
    /* Type of variable */
    GL_FLOAT, 
    /* Flag indicating if we need to normalize data */
    GL_FALSE,
    /* Stride, 0 indicating bytes are tightly packed */ 
    0,
    /* Offset pointer */
    NULL);
  
  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vs_src, NULL );
  glCompileShader(vs);
  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fs_src, NULL );
  glCompileShader(fs);
  program = glCreateProgram();
  glAttachShader(program, vs );
  glAttachShader(program, fs );
  glLinkProgram(program );

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}