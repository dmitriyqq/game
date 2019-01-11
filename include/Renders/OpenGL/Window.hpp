#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../IWindow.hpp"

#include "InputManager.hpp"
#include "ShaderProgram.hpp"

#include <nanogui/nanogui.h>

namespace Glfw {

    class Window : public IWindow {
        GLFWwindow *__window = nullptr;
        Glfw::InputManager __inputManager;
//        OpenGL::ShaderProgram *__used_program = nullptr;
    public:
        explicit Window(int width = 1200, int height = 800) : IWindow(width, height) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            __window = glfwCreateWindow(__width, __height, "Game", nullptr, nullptr);
            if (__window == nullptr) {
                glfwTerminate();
                throw "Failed to create GLFW window";
            }

            glfwMakeContextCurrent(__window);

            // glfwSetInputMode(__window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                throw "Failed to initialize GLAD";
            }

            glEnable(GL_DEPTH_TEST);
            glClearColor(0.07f, 0.09f, 0.09f, 1.0f);
            glViewport(0, 0, __width, __height);
            __inputManager.setupWindow(__window);
        }

        IKeyboardState* getKeyBoardState() override {
            return &__inputManager;
        }

        IKeyboardDirectInput *getKeyboardDirectInput() override {
            return &__inputManager;
        }

        IMouseInput *getMouseInput() override {
            return &__inputManager;
        }

        nanogui::Screen* getScreen() {
            return __inputManager.getScreen();
        }

        void startDisplay() override {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void endDisplay() override {
            if (!glfwWindowShouldClose(__window)) {
                glfwSwapBuffers(__window);
                glfwPollEvents();
            } else {
                exit(69);
            }
        }

        // !TODO investigate how to make this code cleaner and more efficient;
//    void useShaders(OpenGL::ShaderProgram *program){
//        if(__used_program != program){
//            __used_program = program;
//            program->use();
//        }
//    }
        GLFWwindow* getWindow() const { return __window; }

        void setupInputManager() {
            __inputManager.setupWindow(__window);
        }
    };

}