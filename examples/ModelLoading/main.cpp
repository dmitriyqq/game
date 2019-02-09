#include <iostream>
#include <Engine/Game.hpp>
#include <Renders/OpenGL/Window.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>
#include <Renders/OpenGL/ArcBallCamera.hpp>
#include <Renders/OpenGL/Model.hpp>
#include "ModelExplorer.hpp"

class ParticleEngineDemo: public Engine::IGame {
    Glfw::Window *__window = nullptr;
    OpenGL::PositionShaderProgram *__program = nullptr;
    OpenGL::ArcBallCamera *__camera = nullptr;
    OpenGL::Model *__model = nullptr;
    ModelExplorer *__explorer;
    nanogui::Screen *__screen;
public:
    ParticleEngineDemo(){
        __window = new Glfw::Window();
        __program = new OpenGL::PositionShaderProgram();
        __program->loadShaders("./sharedAssets/shaders/useLightShader.vert", "./sharedAssets/shaders/useLightShader.frag");
        __program->setModel(glm::mat4(1));
        __camera = new OpenGL::ArcBallCamera();

        __model = new OpenGL::Model("./sharedAssets/models/viper/viper.obj", __program);

        auto screen = __window->getScreen();
        auto w = new nanogui::Window(screen, "ModelExplorer");
        w->setLayout(new nanogui::GroupLayout());
        auto v = new nanogui::VScrollPanel(w);
        __explorer = new ModelExplorer(v, __model);
        w->center();
        screen->setVisible(true);
        screen->performLayout();
        __screen = screen;
        __window->getMouseInput()->addSubscriber(__camera);
    }

protected:
    void update() override {
        __camera->update(__delta_time, *__window->getKeyBoardState());

        auto width = __window->getWidth();
        auto height = __window->getHeight();
        __program->setCamera(__camera, width, height);
    }

    void draw() const override {
        __window->startDisplay();
        glEnable(GL_DEPTH_TEST);
        __model->draw();
        __screen->drawContents();
        __screen->drawWidgets();
        __window->endDisplay();
    }
};

int main() {
    ParticleEngineDemo demo;
    demo.start();
    std::cout<<"Hello world"<<std::endl;
}