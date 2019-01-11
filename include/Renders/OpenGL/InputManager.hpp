#pragma once

#include <GLFW/glfw3.h>
#include <nanogui/screen.h>
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
    using Engine::Input::IMouseSubscriber;
    using Engine::Input::IKeyboardState;

    class InputManager : public IKeyboardState, public IKeyboardDirectInput, public IMouseInput{
        std::vector <IKeyboardSubscriber*> __kbSubscribers;
        std::vector <IMouseSubscriber*> __mouseSubscribers;

        GLFWwindow *__window = nullptr;
        KeyMap keyMap;

        nanogui::Screen *__screen;

        double mouseX = 0, mouseY = 0;
        double deltaX = 0, deltaY = 0;

        void setupCallbacks(){
            glfwSetWindowUserPointer(__window, this);
            glfwSetCursorPosCallback(__window, handleMouse);
            glfwSetMouseButtonCallback(__window, handleMouseButton);
            glfwSetKeyCallback(__window, handleKeyboard);
            glfwSetScrollCallback(__window, scrollCallback);
            glfwSetFramebufferSizeCallback(__window, framebufferSizeCallback);
        }

        static void charCallback(GLFWwindow *window, unsigned int codepoint){
            auto manager = (InputManager *) glfwGetWindowUserPointer(window);
            manager->__screen->charCallbackEvent(codepoint);
        }

        static void dropCallback(GLFWwindow *window, int count, const char **filenames) {
            auto manager = (InputManager *) glfwGetWindowUserPointer(window);
            manager->__screen->dropCallbackEvent(count, filenames);
        }

        static void scrollCallback(GLFWwindow *window, double x, double y) {
            auto manager = (InputManager *) glfwGetWindowUserPointer(window);
            manager->__screen->scrollCallbackEvent(x, y);
        }

        static void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
            auto manager = (InputManager *) glfwGetWindowUserPointer(window);
            manager->__screen->resizeCallbackEvent(width, height);
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

        void updateMouseDown(Engine::Input::MouseButton key) {
            for(auto &&sub: __mouseSubscribers){
                sub->onMouseDown(key);
            }
        }

        void updateMouseUp(Engine::Input::MouseButton key) {
            for(auto &&sub: __mouseSubscribers){
                sub->onMouseUp(key);
            }
        }

        static void handleMouseButton(GLFWwindow *window, int glfwbtn, int action, int mods) {
            auto manager = (InputManager *) glfwGetWindowUserPointer(window);
            if(!manager->__screen->mouseButtonCallbackEvent(glfwbtn, action, mods)) {
                auto button = Engine::Input::MouseButton::LEFT;

                if (glfwbtn == GLFW_MOUSE_BUTTON_RIGHT) {
                    button = Engine::Input::MouseButton::RIGHT;
                }

                if (action == GLFW_PRESS) {
                    manager->updateMouseDown(button);
                } else {
                    manager->updateMouseUp(button);
                }
            }
        }

        static void handleMouse(GLFWwindow* window, double posx, double posy){
            auto manager = (InputManager *) glfwGetWindowUserPointer(window);
            manager->updateMouse(posx, posy);
            manager->__screen->cursorPosCallbackEvent(posx, posy);
        }

        static void handleKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods){
            auto manager = (InputManager*)glfwGetWindowUserPointer(window);

            if(action == GLFW_PRESS){
                auto k = manager->keyMap.map(key);
                for(auto &&subscriber: manager->__kbSubscribers){
                    subscriber->processKey(k);
                }
            }

            manager->__screen->keyCallbackEvent(key, scancode, action, mods);
        }
    public:
        InputManager() = default;

        explicit InputManager(GLFWwindow *window){
            setupWindow(window);
        }

        void setupWindow(GLFWwindow *window){
            __screen = new nanogui::Screen();
            __screen->initialize(window, false);
            __window = window;
            setupCallbacks();
        }

        nanogui::Screen* getScreen() {
            return __screen;
        }


        void addSubscriber(IKeyboardSubscriber *subscriber) override {
            __kbSubscribers.push_back(subscriber);
        }

        bool isKeyPressed(Engine::Input::Key key) const override {
            int glfwKey = keyMap.map(key);
            return glfwGetKey(__window, glfwKey) == GLFW_PRESS;
        }

        void addSubscriber(Engine::Input::IMouseSubscriber *subscriber) override {
            __mouseSubscribers.push_back(subscriber);
        }
    };
}
