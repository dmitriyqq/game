#pragma once
#include <vector>

#include "../../Engine/IKeyboardDirectInput.hpp"
#include <GLFW/glfw3.h>

namespace Glfw {

    class GlfwKeyboardDirectInput : public Engine::Input::IKeyboardDirectInput {
        GLFWwindow *__window = nullptr;

        std::vector<Engine::Input::IKeyboardSubscriber*> __subscribers;

        static void setupGlfwCallback(GLFWwindow *window){
            glfwSetKeyCallback(window, GlfwCallback);
        }

        static void GlfwCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
            auto context = (GlfwKeyboardDirectInput*)glfwGetWindowUserPointer(window);
            if(action == GLFW_PRESS){
                auto k = mapKey(key);
                for(auto &&subscriber: context->__subscribers){
                    subscriber->processKey(k);
                }
            }
        }

        static Engine::Input::Key mapKey(int glfwKey){
            switch (glfwKey){
                case GLFW_KEY_W: return Engine::Input::Key::UP;
                case GLFW_KEY_S: return Engine::Input::Key::DOWN;
                case GLFW_KEY_A: return Engine::Input::Key::LEFT;
                case GLFW_KEY_D: return Engine::Input::Key::RIGHT;
                case GLFW_KEY_SPACE: return Engine::Input::Key::ACTION;
                case GLFW_KEY_ENTER: return Engine::Input::Key::ACCEPT;
                case GLFW_KEY_ESCAPE: return Engine::Input::Key::EXIT;
                default: return Engine::Input::Key::EXIT;
            }
        }
    public:
        void addSubscriber(Engine::Input::IKeyboardSubscriber *subscriber) override {
            __subscribers.push_back(subscriber);
        }

        void setupWindowInput(GLFWwindow *window){
            __window = window;
            glfwSetWindowUserPointer(__window, this);
            setupGlfwCallback(window);
        }
    };

}
