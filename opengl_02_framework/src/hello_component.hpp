#pragma once
#include <stdio.h>
#ifndef HELLO_COMPONENT_HPP
#define HELLO_COMPONENT_HPP


#include "framework.hpp"

namespace leza {

class HelloComponent : public ComponentAbstract {
 public:
  virtual void Update(GLFWwindow* window) noexcept override {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
};

} // namespace leza

#endif  // HELLO_COMPONENT_HPP