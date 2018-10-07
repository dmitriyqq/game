#pragma once

#include <GLFW/glfw3.h>
#include "Engine/IKeyboardState.hpp"
#include "./GlfwKeyMap.hpp"
namespace Glfw {

    class GlfwKeyboardState : public Engine::Input::IKeyboardState {
        KeyMap keyMap;
        GLFWwindow *__window;
    public:
        explicit GlfwKeyboardState(GLFWwindow *window) {
            __window = window;
        }

        bool isKeyPressed(Engine::Input::Key key) override {
            int glfwKey = keyMap.map(key);
            return glfwGetKey(__window, glfwKey) == GLFW_PRESS;
        }
    };

}