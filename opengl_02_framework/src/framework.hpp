#pragma once
#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <memory>
#include <stdio.h>


#include "GLFW/glfw3.h"
#include "glad/glad.h"  // IWYU pragma: export

namespace leza {
using ProcessInput = void (*)(GLFWwindow *);
class Framework {
public:
  Framework() = delete;
  Framework(const Framework &) = delete;
  Framework(const Framework &&) = delete;
  Framework &operator=(const Framework) = delete;
  Framework &operator=(const Framework &&) = delete;

public:
  Framework(int width, int height, ProcessInput const processInput,
            GLFWframebuffersizefun const framebuffer_size_callback) noexcept;
  int Open();
  int Update();

private:
  int width;
  int height;
  GLFWwindow *window;
  ProcessInput processInput;
  GLFWframebuffersizefun framebuffer_size_callback;
};

class FrameworkBuild {
public:
  std::unique_ptr<Framework> Build() noexcept;
  FrameworkBuild SetWidth(int width) noexcept;
  FrameworkBuild SetHeight(int height) noexcept;
  FrameworkBuild SetProcessInputCallBack(ProcessInput const process_input_callback) noexcept;
  FrameworkBuild SetFramebufferSizeCallback(GLFWframebuffersizefun const framebuffer_size_callback) noexcept;

private:
  int width = 800;
  int height = 600;
  ProcessInput process_input_callback = [](GLFWwindow *) {};
  GLFWframebuffersizefun framebuffer_size_callback =
      [](GLFWwindow *window, int width, int height) {};
};

} // namespace leza

#endif