#pragma once
#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Renders/OpenGL/CubeVAO.hpp>
#include <Renders/OpenGL/Camera.hpp>
#include "../IRenderingBackend.hpp"
#include <iostream>
#include <functional>

#include "Model/Voxel.hpp"
#include "ICamera.hpp"

namespace OpenGL {

    class OpenGLRenderingBackend : public IRenderingBackend {
        static constexpr int WIDTH = 800, HEIGHT = 800;
        ShaderProgram *myProgram;
        GLFWwindow *__window;
        ICamera *__camera;

    public:
        OpenGLRenderingBackend(ICamera *cam): __camera(cam) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            __window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
            if (__window == NULL) {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
            }

            glfwMakeContextCurrent(__window);
            // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            // glfwSetCursorPosCallback(window, OpenGLRenderingBackend::handleMouseMove);
            // glfwSetScrollCallback(window, scroll_callback);

            glfwSetInputMode(__window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD" << std::endl;
            }

            glEnable(GL_DEPTH_TEST);
            glClearColor(0.07f, 0.09f, 0.09f, 1.0f);
            glViewport(0, 0, WIDTH, HEIGHT);
            myProgram = new ShaderProgram();
            myProgram->loadShaders("simpleShader.vert", "simpleShader.frag");
            // myCam = new Camera(vec3(1.0f, 2.0f, 10.0f));
        }

        void useCamera(ICamera *cam){
            __camera = cam;
        }

        GLFWwindow* getWindow(){
            return __window;
        }

        int width() override {
            return 50;
        }

        int height() override {
            return 50;
        }

        void startDisplay() override {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            static CubeVAO myCube;
//            myProgram->use();
//            myProgram->setMat4("view", __camera->getViewMatrix());
//            myProgram->setMat4("projection", __camera->getProjectionMatrix(WIDTH, HEIGHT));
//            glBindVertexArray(myCube.getId());
//            mat4 model1(1);
//            mat4 model2(1);
//            mat4 model3(1);
//            mat4 model4(1);
//
//            model1 = glm::translate(model1, glm::vec3(5.0f, 0.0f, 0.0f));
//            model2 = glm::translate(model2, glm::vec3(0.0f, 5.0f, 0.0f));
//            model3 = glm::translate(model3, glm::vec3(0.0f, 0.0f, 5.0f));
//            myProgram->setMat4("model", model1);
//            myProgram->setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
//            myCube.draw();
//            myProgram->setMat4("model", model2);
//            myProgram->setVec3("color", glm::vec3(0.0f, 1.0f, 0.0f));
//            myCube.draw();
//            myProgram->setMat4("model", model3);
//            myProgram->setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
//            myCube.draw();
//            myProgram->setMat4("model", model4);
//            myProgram->setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
//            myCube.draw();
            glBindVertexArray(myCube.getId());
        }


        void display(const Voxel &voxel, int y, int x) const override {
            static CubeVAO myCube;
            myProgram->use();
            myProgram->setMat4("view", __camera->getViewMatrix());
            myProgram->setMat4("projection", __camera->getProjectionMatrix(WIDTH, HEIGHT));
            mat4 model1(1);
            switch (voxel.type){
                case Voxel::Type::GRASS:
                    myProgram->setVec3("color", glm::vec3(0.0f, 1.0f, 0.0f));
                    break;
                case Voxel::Type::SNOW:
                    myProgram->setVec3("color", glm::vec3(0.7f, 0.7f, 0.7f));
                    break;
                case Voxel::Type::SAND:
                    myProgram->setVec3("color", glm::vec3(1.0f, 1.0f, 0.0f));
                    break;
                case Voxel::Type::ROCK:
                    myProgram->setVec3("color", glm::vec3(0.3f, 0.3f, 0.3f));
                    break;
                case Voxel::Type::AIR:
                    myProgram->setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
                    break;
                case Voxel::Type::WATER:
                    myProgram->setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
                    break;
            }
            model1 = glm::translate(model1, glm::vec3(1.0f * x, 0.0f, 1.0f * y));

            myProgram->setMat4("model", model1);
            //  myProgram->setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
            myCube.draw();


            // std::cout<<"Draw"<<std::endl;
        }

        void endDisplay() override {
            if (!glfwWindowShouldClose(__window)) {
                glfwSwapBuffers(__window);
                glfwPollEvents();
            } else {
                throw "exit";
            }
        }
    };

}
