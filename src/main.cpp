#include <iostream>
#include <thread>
#include "Camera.hpp"
#include "VoxelSpace.hpp"
#include "ISpaceGenerator.hpp"
#include "KeyTable.hpp"
#include "UI.hpp"
#include "Game.hpp"

//template< typename SpaceT, typename UiT>
//class Game : public IGame {
//    SpaceT _space;
//    UiT __ui;
//    KeyTable *keytable;
//
//    void update() override {
//        keytable->update();
//    }
//
//    void draw() const override {
//        __ui.display(&_space);
//    }
//
//public:
//    Game(){
//        auto generator = new PerlynSpaceGenerator();
//        generator->generate(_space, 200, 200, 70);
//
//        keytable = new KeyTable();
//    }
//};

class GameEnd : public IKeyboardSubscriber{
public:
    void processKey(char key) override {
        if(key == 'q'){
            throw std::logic_error("end fucking game");
        }
    }
};

class SnakeCamera{
    NCursesRenderingBackend *__renderingBackend;
public:
    int width(){
        return __renderingBackend->width();
    }

    int height(){
        return __renderingBackend->width();
    }

    SnakeCamera(int width, int height) {
        __renderingBackend = new NCursesRenderingBackend(width, height);
    }

    void display(const std::vector<IDrawable *> &drawables){
        __renderingBackend->startDisplay();
        for(auto &drawable: drawables){
            drawable->draw(__renderingBackend);
        }

        __renderingBackend->endDisplay();
    }
};

class Snake : public IKeyboardSubscriber, public IDrawable{
public:
    int x = 50, y = 50;
    void processKey(char key) override {
        switch (key){
            case 'w': y--; break;
            case 'a': x--; break;
            case 's': y++; break;
            case 'd': x++; break;
            default: break;
        }
    }

    void draw(IRenderingBackend * backend) const override{
        Voxel voxel;
        voxel.type = Voxel::Type::SNOW;
        backend->display(voxel, y, x);
    }
};

template <typename UiT>
class Game : public IGame {
    UiT __ui;
    KeyTable keytable;
    Snake __snake;
    GameEnd __game_end;
    std::vector <IDrawable*> drawables;

    void update() override {
        keytable.update();
        DebugWindow::debug("snakex", __snake.x);
        DebugWindow::debug("snakey", __snake.y);
    }

    void draw() const override {
        __ui.display(drawables);
    }

public:
    Game(){
        keytable.addSubscriber(&__snake);
        keytable.addSubscriber(&__game_end);
        drawables.push_back(&__snake);
    }
};

int main(){
    auto logger = spdlog::basic_logger_mt(Constants::MAIN_LOGGER, "log.txt");
    logger->error("Welcome to spdlog!");
    logger->set_level(spdlog::level::info);
    logger->flush_on(spdlog::level::debug);

    try {
        auto myGame = new Game<UI <SnakeCamera> >();
        myGame->start();
    }
    catch (std::exception & e){
        logger->error("exception_occured " + std::string(e.what()));
        logger->error("shutdown" + std::string(e.what()));
        logger->flush();

        // TODO fix this
        endwin();
        return 23;
    }

    endwin();
    return 0;
}