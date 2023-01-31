#pragma once

#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <stdio.h>
#include <memory>
#include <vector>
#include <utility>

#include "GLFW/glfw3.h"
#include "glad/glad.h" // IWYU pragma: export

namespace leza {

class ComponentAbstract {
public:
  ComponentAbstract() noexcept = default;
  ComponentAbstract(const ComponentAbstract &) = delete;
  ComponentAbstract(const ComponentAbstract &&) = delete;
  ComponentAbstract &operator=(const ComponentAbstract) = delete;
  ComponentAbstract &operator=(const ComponentAbstract &&) = delete;
  ~ComponentAbstract() noexcept = default;

  virtual void Start(GLFWwindow *window) noexcept {}
  virtual void Update(GLFWwindow *window) noexcept {}
  virtual void OnDestroy(GLFWwindow *window) noexcept {}
};

class GameObject {
public:
  using Component = std::unique_ptr<ComponentAbstract>;
  using Components = std::vector<Component>;
  
  GameObject() noexcept;
  GameObject(const GameObject &) = delete;
  GameObject(GameObject &&) noexcept = default;
  GameObject &operator=(const GameObject) = delete;
  GameObject &operator=(GameObject &&) noexcept = default;
  ~GameObject() noexcept = default;

  void AddComponent(Component &&component) noexcept;
  virtual void Start(GLFWwindow *window) noexcept;
  virtual void Update(GLFWwindow *window) noexcept;
  virtual void OnDestroy(GLFWwindow *window) noexcept;

private:
  std::unique_ptr<Components> components;
};

class Framework {
public:
  Framework() = delete;
  Framework(const Framework &) = delete;
  Framework(const Framework &&) = delete;
  Framework &operator=(const Framework) = delete;
  Framework &operator=(const Framework &&) = delete;
  ~Framework() = default;
public:
  Framework(int width, int height,
            GLFWframebuffersizefun const framebuffer_size_callback) noexcept;
  int Open() noexcept;
  int Update() noexcept;
  void AddGameObject(GameObject &&gameObject) noexcept;

private:
  int width;
  int height;
  GLFWwindow *window;
  GLFWframebuffersizefun framebuffer_size_callback;
  std::vector<GameObject> gameObjects{};
};

class FrameworkBuild {
public:
  std::unique_ptr<Framework> Build() noexcept;
  FrameworkBuild SetWidth(int width) noexcept;
  FrameworkBuild SetHeight(int height) noexcept;
  FrameworkBuild SetFramebufferSizeCallback(
      GLFWframebuffersizefun const framebuffer_size_callback) noexcept;

private:
  int width = 800;
  int height = 600;
  GLFWframebuffersizefun framebuffer_size_callback =
      [](GLFWwindow *window, int width, int height) {};
};
} // namespace leza

#endif // FRAMEWORK_HPP