#pragma once

#include <Engine/Game.hpp>
#include <Renders/OpenGL/Window.hpp>
#include <Renders/OpenGL/ShaderProgram.hpp>
#include <Renders/OpenGL/Camera.hpp>
#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/Model.hpp>
#include <Engine/IMouseSubscriber.hpp>
#include <Engine/ISelectable.hpp>
#include <Engine/IUpdatable.hpp>
#include <Renders/OpenGL/Window.hpp>

#include <Engine/Input.hpp>

#include "Renders/OpenGL/ArcBallCamera.hpp"
#include "Map/Map.hpp"

#include "UI/DebugCamera.hpp"

#include <reactphysics3d.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <nanogui/nanogui.h>

#include "ObjectSelector.hpp"
#include "Entities/DynamicEntity.hpp"
#include "Players/HumanPlayer.hpp"
#include "Players/GodPlayer.hpp"
#include "Players/ComputerPlayer.hpp"
#include "MapSelector.hpp"
#include "UI/EntityFactoryWindow.hpp"

class ExitGameESC: public Engine::Input::IKeyboardSubscriber {
    public: 
    void processKey(Engine::Input::Key key) override {
        if (key == Engine::Input::Key::EXIT)
            exit(96);
    }
};

class SpaceWarsGame: public Engine::IGame {
    Glfw::Window *__window = nullptr;
    OpenGL::PositionShaderProgram *__program = nullptr;
    OpenGL::PositionShaderProgram *__debugProgram = nullptr;
    OpenGL::ICamera *__currentCamera = nullptr;

    nanogui::Screen *__screen = nullptr;
    ObjectSelector *__objectSelector = nullptr;
    MapSelector *__mapSelector = nullptr;
    nanogui::Window *__selectedEntityWindow = nullptr;
    DebugCamera *__debugCam = nullptr;
    EntityFactoryWindow *__entityFactoryWindow = nullptr;

    std::vector<Engine::Input::IUpdatableKeytable *> __systems;

    std::vector<Player *> __players;
    Player *__selectedPlayer = nullptr;
    Map *__map = nullptr;

    rp3d::DynamicsWorld *__world;

    // do not forget to dispose it...
    std::vector <OpenGL::Model*> __models;

    UnitsFactory *__unitsFactory = nullptr;
    Unit * __unit = nullptr;

    void updateSystems(float delta_time) {
        for(auto &&system:__systems) {
            system->update(delta_time, *__window->getKeyBoardState());
        }
    }

    void initUI() {
        using namespace nanogui;
        __screen = __window->getScreen();

        __debugCam = new DebugCamera(__screen, __currentCamera);


        __screen->setVisible(true);
        __screen->performLayout();
    }

    void initPrograms() {
        __debugProgram = new OpenGL::PositionShaderProgram();
        __debugProgram->loadShaders("./sharedAssets/shaders/debugShader.vert",
                                  "./sharedAssets/shaders/debugShader.frag");
        __debugProgram->setModel(glm::mat4(1));

        __program = new OpenGL::PositionShaderProgram();
        __program->loadShaders("./sharedAssets/shaders/useLightShader.vert",
                             "./sharedAssets/shaders/useLightShader.frag");
    }

    void createMap() {
        StarsFactory *starsFactory;
        PlanetsFactory *planetsFactory;
        // stars factory
        {
            auto starModel = new OpenGL::Model("./sharedAssets/models/sol/sol.obj", __program);
            auto texture = new Texture("./sharedAssets/icons/sun.png");
            __models.push_back(starModel);
            starsFactory = new StarsFactory(starModel, __world, __program, texture);
        }
        // planets factory
        {
            auto planetModel = new OpenGL::Model("./sharedAssets/models/planet/planet.obj", __program);
            auto texture = new Texture("./sharedAssets/icons/planet.png");
            __models.push_back(planetModel);
            planetsFactory = new PlanetsFactory(planetModel, __world, __program, texture);
        }

        __map = new Map(__program, __debugProgram, starsFactory, planetsFactory);
        __map->constructGalaxy(glm::vec3(0, 0, 0), __players[1]);
    }

    void createPlayers() {
        __players.push_back(new GodPlayer("God Player"));
        __players.push_back(new HumanPlayer("Human Player"));
        __players.push_back(new ComputerPlayer("Computer Player"));

        __selectedPlayer = __players[1];
        // units factory
        __unitsFactory = new UnitsFactory(__world, __program);
        __unit = __unitsFactory->constructUnit(__unitsFactory->getAvailableUnits()[1], __players[0]);


    }

public:
    void registerSystem(Engine::Input::IUpdatableKeytable *updatable) {
        __systems.push_back(updatable);
    }


    SpaceWarsGame() : Engine::IGame(), __world(new rp3d::DynamicsWorld(rp3d::Vector3(0, 0, 0))) {
        __window = new Glfw::Window();
        __world->setIsGratityEnabled(false);

        auto arcBallCamera = new ArcBallCamera();
        arcBallCamera->setZoom(40.0f);
        registerSystem(arcBallCamera);

        __currentCamera = arcBallCamera;

        initPrograms();
        createPlayers();
        createMap();
        initUI();

        auto width = __window->getWidth();
        auto height = __window->getHeight();

        __mapSelector = new MapSelector(__map, __players[1], __debugProgram, __currentCamera, width, height);

        __entityFactoryWindow = new EntityFactoryWindow(__screen, __mapSelector, __players[1], __unitsFactory, width);
        __entityFactoryWindow->center();
        auto padding = (width - __entityFactoryWindow->width())/2.0f;
        __entityFactoryWindow->setPosition(Eigen::Vector2i(padding, height - __entityFactoryWindow->height()));

        __objectSelector = new ObjectSelector(__map, true, __world, __currentCamera, __debugProgram, __program, __selectedPlayer, width, height);
        __objectSelector->setListener([this, width](Entity *e){
            if (__selectedEntityWindow != e->getWindow()) {
                if (__selectedEntityWindow != nullptr) {
                    __screen->removeChild(__selectedEntityWindow);
                }
                __selectedEntityWindow = e->getWindow();

                // HACK, USE REFS
                __selectedEntityWindow->incRef();

                __screen->addChild(__selectedEntityWindow);
                __selectedEntityWindow->requestFocus();
                __selectedEntityWindow->center();
                __selectedEntityWindow->setPosition(Eigen::Vector2i(width  - __selectedEntityWindow->width(), 0.0f));

            }
        });

        __window->getMouseInput()->addSubscriber(arcBallCamera);
        __window->getMouseInput()->addSubscriber(__entityFactoryWindow);
        __window->getMouseInput()->addSubscriber(__mapSelector);
        __window->getMouseInput()->addSubscriber(__objectSelector);
        __window->getKeyboardDirectInput()->addSubscriber(new ExitGameESC());
        __window->getKeyboardDirectInput()->addSubscriber(__objectSelector);
    }

    ~SpaceWarsGame() = default;
protected:
    void update() override {
        if(__delta_time > 0.00001f){
            updateSystems(__delta_time);

            __map->update(__delta_time);
            __world->update(__delta_time);

            for (auto player : __players){
                player->update(__delta_time);
            }

            __unit->update(__delta_time);
            __entityFactoryWindow->update(__delta_time);
        }

        __debugCam->update();

        auto width = __window->getWidth();
        auto height = __window->getHeight();

        __program->setCamera(__currentCamera, width, height);
        __debugProgram->setCamera(__currentCamera, width, height);

    }

    void draw() const override {
        __window->startDisplay();

        __map->draw();

        for (auto player : __players){
            player->draw();
        }

        __objectSelector->draw();
        __mapSelector->draw();
        __unit->draw();
        __entityFactoryWindow->draw();
        __screen->drawContents();
        __screen->drawWidgets();

        __window->endDisplay();
    }
};