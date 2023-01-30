#include "framework.hpp"
#include <memory>
#include <stdio.h>

namespace leza {

Framework::Framework(int width, int height, ProcessInput processInput,
                     GLFWframebuffersizefun framebuffer_size_callback) noexcept
    : width(width), height(height), processInput(processInput),
      framebuffer_size_callback(framebuffer_size_callback) {}

int Framework::Open() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");
    return -1;
  }

  return 0;
}

int Framework::Update() {

  if (glfwWindowShouldClose(window))
    return -1;
  // input
  // -----
  processInput(window);

  // render
  // ------
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
  // etc.)
  // -------------------------------------------------------------------------------
  glfwSwapBuffers(window);
  glfwPollEvents();
  return 0;
}

std::unique_ptr<Framework> FrameworkBuild::Build() noexcept {
  std::unique_ptr<Framework> ret = std::make_unique<Framework>(
      width, height, process_input_callback, framebuffer_size_callback);
  return ret;
}

FrameworkBuild FrameworkBuild::SetWidth(int width) noexcept {
  this->width = width;
  return *this;
}
FrameworkBuild FrameworkBuild::SetHeight(int height) noexcept {
  this->height = height;
  return *this;
}
FrameworkBuild FrameworkBuild::SetProcessInputCallBack(
    ProcessInput const process_input_callback) noexcept {
  this->process_input_callback = process_input_callback;
  return *this;
}
FrameworkBuild FrameworkBuild::SetFramebufferSizeCallback(
    GLFWframebuffersizefun const framebuffer_size_callback) noexcept {
  this->framebuffer_size_callback = framebuffer_size_callback;
  return *this;
}

} // namespace leza