#include <iostream>
#include <Engine/Game.hpp>
#include <Renders/OpenGL/Window.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>
#include <Renders/OpenGL/ArcBallCamera.hpp>
#include "ParticleEngine.hpp"

class ParticleEngineDemo: public Engine::IGame {
    Glfw::Window *__window = nullptr;
    ParticleEngine *__demo = nullptr;
    OpenGL::PositionShaderProgram *__program = nullptr;
    OpenGL::ArcBallCamera *__camera;
public:
    ParticleEngineDemo(){
        __window = new Glfw::Window();
        __demo = new ParticleEngine(100000, glm::vec3(0.0f, 0.0f, 0.0f));
        __program = new OpenGL::PositionShaderProgram();
        __program->loadShaders("./sharedAssets/shaders/particlesProgram.vert", "./sharedAssets/shaders/particlesProgram.frag");
        __camera = new OpenGL::ArcBallCamera();

        __window->getMouseInput()->addSubscriber(__camera);
    }

protected:
    void update() override {
        __demo->update(__delta_time);
        __camera->update(__delta_time, *__window->getKeyBoardState());

        auto width = __window->getWidth();
        auto height = __window->getHeight();
        __program->setCamera(__camera, width, height);
        __program->setVec3("cameraUp", __camera->getUpVector());
        __program->setVec3("cameraRight", __camera->getRightVector());
        __program->setFloat("time", __ticks / 100.0f);
    }

    void draw() const override {
        __window->startDisplay();
        __program->use();
        __demo->draw();
        __window->endDisplay();
    }
};

int main() {
    ParticleEngineDemo demo;
    demo.start();
    std::cout<<"Hello world"<<std::endl;
}