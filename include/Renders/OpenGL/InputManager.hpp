#pragma once

#include <GLFW/glfw3.h>
#include <vector>

#include <Engine/IKeyboardSubscriber.hpp>
#include <Engine/IKeyboardDirectInput.hpp>
#include <Engine/IKeyboardState.hpp>
#include <Engine/IMouseSubscriber.hpp>
#include <Engine/IMouseInput.hpp>
#include "GlfwKeyMap.hpp"

namespace Glfw{
    using Engine::Input::IKeyboardSubscriber;
    using Engine::Input::IKeyboardDirectInput;
    using Engine::Input::IMouseInput;
    using Engine::Input::IKeyboardState;

    class InputManager : public IKeyboardState, public IKeyboardDirectInput, public IMouseInput{
        std::vector <Engine::Input::IKeyboardSubscriber*> __kbSubscribers;
        std::vector <Engine::Input::IMouseSubscriber*> __mouseSubscribers;

        GLFWwindow *__window;
        KeyMap keyMap;

        double mouseX = 0, mouseY = 0;
        double deltaX = 0, deltaY = 0;

        void setupCallbacks(){
            glfwSetWindowUserPointer(__window, this);
            glfwSetCursorPosCallback(__window, handleMouse);
            glfwSetKeyCallback(__window, handleKeyboard);
            // glfwSet
        }

        void updateMouse(double newX, double newY){
            deltaX = newX - mouseX;
            deltaY = newY - mouseY;
            mouseX = newX;
            mouseY = newY;
            for(auto &&sub: __mouseSubscribers){
                sub->update(newX, newY, deltaX, deltaY);
            }
        }

        static void handleMouse(GLFWwindow* window, double xpos, double ypos){
            auto manager = (InputManager *) glfwGetWindowUserPointer(window);
            manager->updateMouse(xpos, ypos);
        }

        static void handleKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods){
            auto context = (InputManager*)glfwGetWindowUserPointer(window);

            // dirty fix to undefined reference to static member
            if(action == GLFW_PRESS){
                auto k = context->keyMap.map(key);
                for(auto &&subscriber: context->__kbSubscribers){
                    subscriber->processKey(k);
                }
            }
        }
    public:
        InputManager(GLFWwindow *window){
            __window = window;
            setupCallbacks();
        }

        void addSubscriber(IKeyboardSubscriber *subscriber) override {
            __kbSubscribers.push_back(subscriber);
        }

        bool isKeyPressed(Engine::Input::Key key) override {
            int glfwKey = keyMap.map(key);
            return glfwGetKey(__window, glfwKey) == GLFW_PRESS;
        }

        void addSubscriber(Engine::Input::IMouseSubscriber *subscriber) override {
            __mouseSubscribers.push_back(subscriber);
        }
    };
}