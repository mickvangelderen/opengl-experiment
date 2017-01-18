#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

// Include GLFW after the OpenGL bindings.
#include <GLFW/glfw3.h>

using namespace gl;

int main(void) {
  GLFWwindow* window;

  if (!glfwInit()) return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glbinding::Binding::initialize();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  
  return 0;
}