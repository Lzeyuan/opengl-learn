#include "framework.hpp"
#include <iostream>


using namespace std;

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) noexcept {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) noexcept {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

int main(int argc, char **argv) {
  auto t = leza::FrameworkBuild()
               .SetProcessInputCallBack(processInput)
               .SetFramebufferSizeCallback(framebuffer_size_callback)
               .Build();
  t->Open();
  while (0 == t->Update())
    ;
  return 0;
}
