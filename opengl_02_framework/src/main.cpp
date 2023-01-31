#include <iostream>
#include <memory>
#include <stdio.h>
#include <utility>

#include "hello_component.hpp"
#include "framework.hpp"


using namespace std;

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) noexcept {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

int main(int argc, char **argv) {
  auto framework = leza::FrameworkBuild()
               .SetFramebufferSizeCallback(framebuffer_size_callback)
               .Build();

  #pragma region 手动装配GameObject和component
  leza::GameObject gameObject {};
  std::unique_ptr<leza::ComponentAbstract> helloComponent{new leza::HelloComponent()};
  gameObject.AddComponent(std::move(helloComponent));
  framework->AddGameObject(std::move(gameObject));
  #pragma endregion

  framework->Open();
  while (0 == framework->Update())
    ;
  return 0;
}
