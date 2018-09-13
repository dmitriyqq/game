#include <iostream>
#include <thread>
#include "Camera.hpp"
#include "VoxelSpace.hpp"
#include "ISpaceGenerator.hpp"
#include "KeyTable.hpp"
#include "UI.hpp"

template< typename SpaceT, typename UiT>
class Game{
    SpaceT _space;
    UiT __ui;
    KeyTable *keytable;

    std::chrono::system_clock::time_point lastTime;

    static constexpr float DESIRED_LOGIC_FPS = 30;
    static constexpr float DESIRED_RENDER_FPS = 1;

    float desiredLogicDeltaTime = 1.0f / DESIRED_LOGIC_FPS;
    float desiredRenderDeltaTime = 1.0f / DESIRED_RENDER_FPS;

    float logicDeltaTime, renderDeltaTime;

    bool isPlaying = false;


    void gameLoop(){
        auto newTime = std::chrono::system_clock::now();
        float delta = (std::chrono::duration_cast<std::chrono::milliseconds>(lastTime - newTime).count() / 1000.0f);

        logicDeltaTime += delta;
        renderDeltaTime += delta;

        if(logicDeltaTime > desiredLogicDeltaTime) {
            update();
        }

        if(renderDeltaTime > desiredLogicDeltaTime){
            draw();
        }

        lastTime = newTime;
        gameLoop();
    }

public:
    Game(){
        auto logger = spdlog::get("main_logger");
        logger->info("Creating Game");

        auto generator = new PerlynSpaceGenerator();
        generator->generate(_space, 200, 200, 70);

        keytable = new KeyTable();
    }

    void start(){
        isPlaying = true;
        gameLoop();
    }

    void finish(){
        isPlaying = false;
    }

    void update(){
        keytable->update();

//        if( c == 'q'){
//             TODO fix this
//            throw "EXITFUCKINGGAME";
//        }
    }

    void draw(){
        __ui.display(&_space);
    }

};

int main(){
    auto logger = spdlog::basic_logger_mt("main_logger", "log.txt");
    logger->error("Welcome to spdlog!");
    logger->set_level(spdlog::level::warn);
    logger->flush_on(spdlog::level::debug);

    try {
        auto myGame = new Game<SimpleSpace, UI>();
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
    //getch();
    endwin();
    return 0;
}