#include <Engine/Game.hpp>
#include <Renders/OpenGL/Texture.hpp>
#include <Renders/OpenGL/Window.hpp>
#include <Renders/OpenGL/ShaderProgram.hpp>
#include <Renders/OpenGL/DirectLight.hpp>
#include <Renders/OpenGL/FpsLikeCamera.hpp>
#include <Renders/OpenGL/CubeVAO.hpp>
#include <Renders/OpenGL/Camera.hpp>
#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/Model.hpp>
#include <Engine/IMouseSubscriber.hpp>
#include <Engine/ISelectable.hpp>
#include <Renders/OpenGL/Window.hpp>
#include <Renders/OpenGL/MeshWithBoundingBox.hpp>
#include <Renders/OpenGL/Graphics2D.hpp>

#include <Engine/Input.hpp>

#include "ArcBallCamera.hpp"

#include "Entities/Planet.hpp"
#include "Entities/Viper.hpp"
#include "Entities/Asteroid.hpp"

#include <reactphysics3d.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <nanogui/nanogui.h>

#include "Entities/Star.hpp"

class ExitGameESC: public Engine::Input::IKeyboardSubscriber {
    public: 
    void processKey(Engine::Input::Key key) override {
        if (key == Engine::Input::Key::EXIT)
            throw "exit";
    }
};

class RaycastCallback : public rp3d::RaycastCallback, public IDrawable{
    OpenGL::Mesh *__mesh = nullptr;

    virtual rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) { 

        // Display the world hit point coordinates 
        std::cout << "Hit point : " << 
                    info.worldPoint.x << 
                    info.worldPoint.y << 
                    info.worldPoint.z << 
                    std::endl; 
        __mesh->setPosition(info.worldPoint.x, info.worldPoint.y, info.worldPoint.z);
        // Return a fraction of 1.0 to gather all hits 
        return rp3d::decimal(0.0); 
    }

    public:
    RaycastCallback(OpenGL::Mesh *mesh): __mesh(mesh) {}

    void draw() const override {
        __mesh->draw();
    }
};

class ObjectSelector: public Engine::Input::IMouseSubscriber, public IDrawable {
    std::vector<Engine::ISelectable*> __selectables;

    double __x = 0, __y = 0;
    double __width;
    double __height;

    rp3d::DynamicsWorld *__world = nullptr;
    RaycastCallback *__callback;
    OpenGL::Mesh *__mesh = nullptr;
    OpenGL::ICamera *__camera = nullptr;
public:
    ObjectSelector(
        rp3d::DynamicsWorld *world,
        OpenGL::ICamera *camera,
        OpenGL::Mesh *mesh,
        double width,
        double height):
        __world(world),
        __camera(camera),
        __width(width),
        __height(height),
        __mesh(mesh) {
            __callback = new RaycastCallback(mesh);
    }

    void draw() const override {
        __callback->draw();
    }

    virtual void update(double x, double y, double dx, double dy) override {
        __x = x;
        __y = y;
    }

    virtual void onMouseUp(Engine::Input::MouseButton key) {
    };

    virtual void onMouseDown(Engine::Input::MouseButton key) {
        glm::vec4 p;
        p.x = -2 * (__x - __width / 2) / __width;
        p.y = -2 * (__y - __height / 2) / __height;
        p.z = 0;

        auto xx = p.x * __camera->getRightVector();
        auto yy = p.y * __camera->getUpVector();

        auto tt = __camera->getPosition();

        rp3d::Vector3 start(tt.x + xx.x + yy.x, tt.y + xx.y + yy.y, tt.z  + xx.z + yy.z);
        auto f = 100.0f * __camera->getForwardVector();
        rp3d::Vector3 end(start.x + f.x, start.y + f.y, start.z + f.z);
        rp3d::Ray ray(start, end);

        __world->raycast(ray, __callback);
    };
};

class TestGame: public Engine::IGame {
    Glfw::Window *__window = nullptr;
    DirectLight *light;
    OpenGL::PositionShaderProgram *program;
    ArcBallCamera *arcBall;
    nanogui::FormHelper *gui;
    nanogui::Screen *screen;
    OpenGL::Model *__planetModel;
    OpenGL::Model *__viperModel;
    OpenGL::Model *__asteroidModel;
    ObjectSelector *__selector;
    OpenGL::MeshWithBoundingBox *mmesh;
    Texture *texture;
    rp3d::DynamicsWorld __world;
    Star *__stars[1000];
    OpenGL::Model *__pmodels[10];
    int __num_of_models = 5;
    DynamicEntity *__entity[1000];
    int __num_entities = 0;
    int x = 10000;


    void initPrograms() {
        // uiProgram = new UIProgram();
        // planetsProgram = new PlanetsProgram();
        program = new OpenGL::PositionShaderProgram();
        program->loadShaders("./sharedAssets/shaders/useLightShader.vert",
         "./sharedAssets/shaders/useLightShader.frag");
    }

    float getRnd() const {
        return (rand()%2 ? 1.0f : -1.0f ) * (rand()%2000) / (float) (rand()%100);
    }

    glm::vec3 getRndVec3() const {
        return glm::vec3(getRnd(), 0.01f, getRnd());
    }

    void addObject(DynamicEntity *e) {
        __entity[__num_entities] = e;
        e->addToWorld(__world, 3.0f*getRndVec3());
        __num_entities++;
        x-=100;
    }

    void addObject() {
        if ( x > 100 ) {
            if(rand()%5 == 0) {
                addViper();
            } else {
                addAsteroid();
            }
        }
    }

    void addViper() {
        DynamicEntity *e = new Viper(program, __viperModel, glm::vec3(0.1f, 0.1f, 0.1f));
        auto v = getRndVec3();
        v.y = 10.0f;
        addObject(e);
    }

    void addAsteroid() {
        DynamicEntity *e = new Asteroid(program, __asteroidModel, glm::vec3(0.1f, 0.1f, 0.1f), 1.1f * getRndVec3());
        auto v = getRndVec3();
        v.y = 10.0f;
        addObject(e);
    }

public:
    void initUI() {
        using namespace nanogui;
        nanogui::init();
        screen = __window->getScreen();
        gui = new FormHelper(screen);
        ref<Window> window = gui->addWindow(Eigen::Vector2i(10, 10), "Object creator");
        gui->addVariable("Resources", x);
        gui->addButton("Create object", [&](){ addObject(); });

        screen->setVisible(true);
        screen->performLayout();
        window->center();
        // nanogui::mainloop();
    }

    TestGame() : Engine::IGame(), __world(rp3d::Vector3(0, 0, 0)) {
        __window = new Glfw::Window();
        texture = new Texture("./sharedAssets/models/nanosuit/glass_dif.png");
        initPrograms();
        initUI();
        light = new DirectLight();
        __world.setIsGratityEnabled(false);

        __planetModel = new OpenGL::Model("./sharedAssets/planets/planet.obj", program);
        __viperModel = new OpenGL::Model("./sharedAssets/models/viper/viper.obj", program);

        __pmodels[1] = new OpenGL::Model("./sharedAssets/models/moon/moon.obj", program);
        __pmodels[2] = new OpenGL::Model("./sharedAssets/models/earth/earth.obj", program);
        __pmodels[0] = new OpenGL::Model("./sharedAssets/models/planet/planet.obj", program);
        __pmodels[3] = new OpenGL::Model("./sharedAssets/models/sol/sol.obj", program);
        __pmodels[4] = new OpenGL::Model("./sharedAssets/models/venus/venus.obj", program);
        __asteroidModel = new OpenGL::Model("./sharedAssets/models/asteroid/asteroid.obj", program);

        mmesh = new OpenGL::MeshWithBoundingBox(program, __planetModel);
        mmesh->setScale(0.1f,0.1f,0.1f);
        for(int i = 0; i < 10; i++) {
            __stars[i] = new Star(__pmodels[rand()%__num_of_models], program,
            __world.createRigidBody(rp3d::Transform::identity()), 3.0f * getRndVec3(), 5.0f);
        }

        for(int i = 0; i < 50; i++) {
            addObject();
        }

        // light = new DirectLight();
        // camera = new OpenGL::FpsLikeCamera();
        arcBall = new ArcBallCamera();
        arcBall->setZoom(40.0f);

        auto width = __window->getWidth();
        auto height = __window->getHeight();
        __selector = new ObjectSelector(&__world, arcBall, mmesh, width, height);
        OpenGL::Graphics2D::get()->setScreenSize(width, height);

        __window->getMouseInput()->addSubscriber(arcBall);
        __window->getMouseInput()->addSubscriber(__selector);
        __window->getKeyboardDirectInput()->addSubscriber(new ExitGameESC());
        // light->uniform(program);

        // auto camera = new Camera2D();
        // bump = new Texture("./sharedAssets/planets/bump1.jpg");
    }

    ~TestGame() = default;
protected:
    void update() override {
        arcBall->update(__delta_time, *__window->getKeyBoardState());

        if(__delta_time > 0.00001f){
            for(int i = 0; i < __num_entities; i++) {
                __entity[i]->update(__delta_time);
            }
            __world.update(__delta_time);
        }
    }

    void draw() const override {
        __window->startDisplay();
        
        glEnable(GL_DEPTH_TEST);
        program->use();

        auto width = __window->getWidth();
        auto height = __window->getHeight();

        program->setCamera(arcBall, width, height);

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