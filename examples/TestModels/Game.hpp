#include <Engine/Game.hpp>
#include <Renders/OpenGL/Texture.hpp>
#include <Renders/OpenGL/Window.hpp>
#include <Renders/OpenGL/ShaderProgram.hpp>
#include <Renders/OpenGL/DirectLight.hpp>
#include <Renders/OpenGL/FpsLikeCamera.hpp>
#include <Renders/OpenGL/CubeVAO.hpp>

#include "./ImageAtlas.hpp";
#include "./Model.hpp"
#include "Camera2D.hpp"

class ExitGameESC: public Engine::Input::IKeyboardSubscriber {
    public: 
    void processKey(Engine::Input::Key key) override {
        if (key == Engine::Input::Key::EXIT)
            throw "exit";
    }
};

class TestGame: public Engine::IGame {
    IWindow * __window = nullptr;
    Model *model;
    OpenGL::ShaderProgram *program;
    OpenGL::ShaderProgram *uiProgram;
    OpenGL::ShaderProgram *modelProgram;
    DirectLight *light;
    OpenGL::FpsLikeCamera *camera;
    OpenGL::CubeVAO *cube;
    ImageAtlas *atlas;
    Sprite *ok;
public:
    TestGame() : Engine::IGame() {
       __window = new Glfw::Window();
        atlas = new ImageAtlas();
        program = new OpenGL::ShaderProgram();
        program->loadShaders("./sharedAssets/shaders/useLightShader.vert",
            "./sharedAssets/shaders/useLightShader.frag");
        uiProgram = new OpenGL::ShaderProgram();
        uiProgram->loadShaders("./sharedAssets/shaders/2dshader.vert",
            "./sharedAssets/shaders/2dshader.frag");
        model = new Model("./sharedAssets/planets/planet.obj");

        modelProgram = new OpenGL::ShaderProgram();
        modelProgram->loadShaders("./sharedAssets/shaders/model.vert",
            "./sharedAssets/shaders/model.frag");
        light = new DirectLight();
        camera = new OpenGL::FpsLikeCamera();
        cube = new OpenGL::CubeVAO();
        __window->getMouseInput()->addSubscriber(camera);
        __window->getKeyboardDirectInput()->addSubscriber(new ExitGameESC());
        program->use();
        Material mat;
        mat.diffuse.r = 0.2;
        mat.diffuse.g = 0.0;
        mat.diffuse.b = 0.2;
        mat.specular.r = 1.0;
        mat.specular.g = 0.0;
        mat.specular.b = 1.0;
        mat.shininess = 0.2;
        glm::mat4 m(1);
        m = glm::scale(m, glm::vec3(0.4, 0.4, 0.4));

        program->use();
        program->setMat4("model", m);
        program->setMaterial(mat);
        light->uniform(program);

        auto camera = new Camera2D();
        uiProgram->use();
        uiProgram->setCamera(camera, __window->getWidth(), __window->getHeight());
        uiProgram->setMat4("model", m);
        ok = atlas->getFrame("ok.png");
        modelProgram->use();
        modelProgram->setMat4("model", m);
    }

    ~TestGame() = default;
protected:
    void update() override {
        camera->update(__delta_time, *__window->getKeyBoardState());
    }

    void draw() const override {
        __window->startDisplay();
        program->use();
        program->setCamera(camera, __window->getWidth(), __window->getHeight());
        modelProgram->use();
        modelProgram->setCamera(camera, __window->getWidth(), __window->getHeight());
        model->Draw(*program);
        cube->draw();
        uiProgram->use();
        glm::mat4 m(1);
        m = glm::scale(m, glm::vec3(50, 50, 50));
        uiProgram->setMat4("model", m);
        ok->draw();
        __window->endDisplay();
    }
};