#include "framework.hpp"
#include <memory>
#include <stdio.h>
#include <utility>

namespace leza {

GameObject::GameObject() noexcept {
  this->components = std::make_unique<Components>();
}

void GameObject::AddComponent(std::unique_ptr<ComponentAbstract>&& component) noexcept {
  components->emplace_back(std::move(component));
}
void GameObject::Start(GLFWwindow *window) noexcept {
  // for (const auto& component : components) {
  //   component->Start(window);
  // }
}
void GameObject::Update(GLFWwindow *window) noexcept {
  for (const auto& component : *components) {
    component->Update(window);
  }
}
void GameObject::OnDestroy(GLFWwindow *window) noexcept {
  // for (const auto& component : components) {
  //   component->OnDestroy(window);
  // }
}


Framework::Framework(int width, int height,
                     GLFWframebuffersizefun framebuffer_size_callback) noexcept
    : width(width), height(height),
      framebuffer_size_callback(framebuffer_size_callback) {
  
}

int Framework::Open() noexcept {
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

int Framework::Update() noexcept {

  if (glfwWindowShouldClose(window))
    return -1;

  for (auto& gameObject : gameObjects) {
    gameObject.Update(window);
  }

  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
  // etc.)
  // -------------------------------------------------------------------------------
  glfwSwapBuffers(window);
  glfwPollEvents();
  return 0;
}

void Framework::AddGameObject(GameObject&& gameObject) noexcept {
  gameObjects.emplace_back(std::move(gameObject));
}

std::unique_ptr<Framework> FrameworkBuild::Build() noexcept {
  std::unique_ptr<Framework> ret =
      std::make_unique<Framework>(width, height, framebuffer_size_callback);
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

FrameworkBuild FrameworkBuild::SetFramebufferSizeCallback(
    GLFWframebuffersizefun const framebuffer_size_callback) noexcept {
  this->framebuffer_size_callback = framebuffer_size_callback;
  return *this;
}

} // namespace leza