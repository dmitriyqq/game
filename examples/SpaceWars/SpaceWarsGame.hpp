#pragma once

#include <Engine/Game.hpp>
#include <Renders/OpenGL/Window.hpp>
#include <Renders/OpenGL/ShaderProgram.hpp>
#include <Renders/OpenGL/Camera.hpp>
#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/Model.hpp>
#include <Engine/IMouseSubscriber.hpp>
#include <Engine/ISelectable.hpp>
#include <Renders/OpenGL/Window.hpp>

#include <Engine/Input.hpp>

#include "ArcBallCamera.hpp"
#include "Map/Map.hpp"

#include "UI/DebugCamera.hpp"

#include <reactphysics3d.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <nanogui/nanogui.h>

#include "ObjectSelector.hpp"
#include "Entities/DynamicEntity.hpp"

class ExitGameESC: public Engine::Input::IKeyboardSubscriber {
    public: 
    void processKey(Engine::Input::Key key) override {
        if (key == Engine::Input::Key::EXIT)
            throw "exit";
    }
};

class SpaceWarsGame: public Engine::IGame {
    Glfw::Window *__window = nullptr;
    OpenGL::PositionShaderProgram *program = nullptr;
    OpenGL::PositionShaderProgram *debugProgram = nullptr;
    OpenGL::ICamera *__currentCamera = nullptr;


    OpenGL::Model *__viperModel;
    OpenGL::Model *__asteroidModel;

    nanogui::FormHelper *gui;
    nanogui::Screen *screen;

    ObjectSelector *__selector;

    std::vector<Player *> __players;

    Map *__map = nullptr;
    DebugCamera *__debugCam;
    rp3d::DynamicsWorld *__world;

    Star *__stars[1000];
    OpenGL::Model *__pmodels[10];
    DynamicEntity *__entity[1000];
    int __num_entities = 0;
    int x = 10000;


    void initPrograms() {
        debugProgram = new OpenGL::PositionShaderProgram();
        debugProgram->loadShaders("./sharedAssets/shaders/debugShader.vert",
                             "./sharedAssets/shaders/debugShader.frag");
        program = new OpenGL::PositionShaderProgram();
        program->loadShaders("./sharedAssets/shaders/useLightShader.vert",
         "./sharedAssets/shaders/useLightShader.frag");
    }

public:
    void initUI() {
        using namespace nanogui;
        nanogui::init();
        screen = __window->getScreen();
//        gui = new FormHelper(screen);
//        ref<Window> window = gui->addWindow(Eigen::Vector2i(10, 10), "Object creator");
//        gui->addVariable("Resources", x);
//        gui->addButton("Create object", [&](){ addObject(); });

        __debugCam = new DebugCamera(screen, __currentCamera);

        screen->setVisible(true);
        screen->performLayout();

//        window->center();
    }

    SpaceWarsGame() : Engine::IGame(), __world(new rp3d::DynamicsWorld(rp3d::Vector3(0, 0, 0))) {
        __window = new Glfw::Window();
        __world->setIsGratityEnabled(false);

        initPrograms();
        debugProgram->setModel(glm::mat4(1));


        __players.emplace_back(new );

        __planetModel = new OpenGL::Model("./sharedAssets/planets/planet.obj", program);
        __viperModel = new OpenGL::Model("./sharedAssets/models/viper/viper.obj", program);

        __pmodels[1] = new OpenGL::Model("./sharedAssets/models/moon/moon.obj", program);
        __pmodels[2] = new OpenGL::Model("./sharedAssets/models/earth/earth.obj", program);
        __pmodels[0] = new OpenGL::Model("./sharedAssets/models/planet/planet.obj", program);
        __pmodels[3] = new OpenGL::Model("./sharedAssets/models/sol/sol.obj", program);
        __pmodels[4] = new OpenGL::Model("./sharedAssets/models/venus/venus.obj", program);
        __asteroidModel = new OpenGL::Model("./sharedAssets/models/asteroid/asteroid.obj", program);


        auto arcBallCamera = new ArcBallCamera();
        arcBallCamera->setZoom(40.0f);
        __window->getMouseInput()->addSubscriber(arcBallCamera);

        __currentCamera = arcBallCamera;

        initUI();

        auto width = __window->getWidth();
        auto height = __window->getHeight();

        __map = new Map(__currentCamera, debugProgram);
        __selector = new ObjectSelector(__map, true, __world, __currentCamera, debugProgram, program, width, height);
        OpenGL::Graphics2D::get()->setScreenSize(width, height);
        __window->getMouseInput()->addSubscriber(__selector);
        __window->getKeyboardDirectInput()->addSubscriber(new ExitGameESC());
        __window->getKeyboardDirectInput()->addSubscriber(__selector);
    }

    ~SpaceWarsGame() = default;
protected:
    void update() override {
        arcBall->update(__delta_time, *__window->getKeyBoardState());

        if(__delta_time > 0.00001f){
            for(int i = 0; i < __num_entities; i++) {
                __entity[i]->update(__delta_time);
            }
            __world.update(__delta_time);
        }

        __debugCam->update();

        auto width = __window->getWidth();
        auto height = __window->getHeight();

        program->setCamera(__currentCamera, width, height);
        debugProgram->setCamera(__currentCamera, width, height);

    }

    void draw() const override {
        __window->startDisplay();
        
        program->use();



        for(int i = 0; i < 10; i++) {
            __stars[i]->draw();
        }

        for(int i = 0; i < __num_entities; i++) {
            __entity[i]->draw();
        }


        __selector->draw();

        screen->drawContents();
        screen->drawWidgets();

        __window->endDisplay();
    }
};