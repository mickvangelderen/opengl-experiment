#include <glbinding/gl33core/gl.h>
#include <glbinding/Binding.h>
// Include GLFW after the OpenGL bindings. Ensure GL/gl.h is not included.
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

using namespace gl33core;

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLuint create_shader(const char * const path, GLenum type);

int main(void) {

  if (!glfwInit()) return -1;

  glfwSetErrorCallback(error_callback);

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "opengl-experiment", monitor, NULL);
  glfwSetKeyCallback(window, key_callback);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glbinding::Binding::initialize();

  glfwSwapInterval(1);

  GLsizei width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport((GLint)0, (GLint)0, width, height);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // Create program.
  GLuint simple_vertex_shader_id = create_shader("assets/simple.vertex.glsl", GL_VERTEX_SHADER);
  GLuint simple_fragment_shader_id = create_shader("assets/simple.fragment.glsl", GL_FRAGMENT_SHADER);
  GLuint simple_program_id = glCreateProgram();
  glAttachShader(simple_program_id, simple_vertex_shader_id);
  glAttachShader(simple_program_id, simple_fragment_shader_id);
  glLinkProgram(simple_program_id);
  GLint simple_program_status;
  glGetProgramiv(simple_program_id, GL_LINK_STATUS, &simple_program_status);
  if ((GLboolean) simple_program_status != GL_TRUE) {
    GLint simple_program_log_length;
    glGetProgramiv(simple_program_id, GL_INFO_LOG_LENGTH, &simple_program_log_length);
    GLchar * simple_program_log =  new GLchar[simple_program_log_length];
    glGetProgramInfoLog(simple_program_id, simple_program_log_length, NULL, simple_program_log);
    std::cerr << simple_program_log << std::endl;
    delete[] simple_program_log;
  }
  glUseProgram(simple_program_id);
  glDeleteShader(simple_vertex_shader_id);
  simple_vertex_shader_id = 0;
  glDeleteShader(simple_fragment_shader_id);
  simple_fragment_shader_id = 0;

  // Create vertex buffer.
  GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
  };

  GLuint vertex_buffer_id;
  glGenBuffers(1, &vertex_buffer_id);
  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);

  glBindVertexArray(vertex_array_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Poll for and process events */
    glfwPollEvents();

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(simple_program_id);
    glBindVertexArray(vertex_array_id);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}

void error_callback(int error, const char* description) {
  std::cerr << "Error: " << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  std::cout << "key_callback"
    << " key: " << key
    << " scancode: " << scancode
    << " action: " << action
    << " mods: " << mods << std::endl;
  switch (action) {
  case GLFW_PRESS:
    switch (key) {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, GLFW_TRUE);
      break;
    }
    break;
  }
}


GLuint create_shader(const char * const path, GLenum type) {
  // Read shader from disk.
  std::ifstream shader_source_stream(path, std::ios::in | std::ios::binary | std::ios::ate);
  GLint shader_source_length = shader_source_stream.tellg();
  shader_source_stream.seekg(0);
  GLchar * shader_source = new GLchar[shader_source_length + 1];
  shader_source_stream.read(shader_source, shader_source_length);
  shader_source[shader_source_length] = '\0';

  // Create shader.
  GLuint shader_id = glCreateShader(type);
  glShaderSource(shader_id, 1, &shader_source, &shader_source_length);
  delete[] shader_source;

  // Compile shader.
  glCompileShader(shader_id);
  GLint shader_compile_status;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compile_status);
  if ((GLboolean) shader_compile_status != GL_TRUE) {
    GLint shader_log_length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &shader_log_length);
    GLchar * shader_log =  new GLchar[shader_log_length];
    glGetShaderInfoLog(shader_id, shader_log_length, NULL, shader_log);
    std::cerr << shader_log << std::endl;
    delete[] shader_log;
  }

  return shader_id;
}
