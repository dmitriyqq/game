#include <iostream>
#include <thread>
#include "Utils/Constants.hpp"
#include "Camera.hpp"
#include "Model/VoxelSpace.hpp"
#include "Model/ISpaceGenerator.hpp"
#include "Renders/Console/KeyTable.hpp"
#include "Renders/Console/UI.hpp"
#include "Engine/Game.hpp"
#include "Renders/OpenGL/OpenGLRenderingBackend.hpp"

#include <queue>

class GameEnd : public IKeyboardSubscriber{
public:
    void processKey(char key) override {
        if(key == 'q'){
            throw std::logic_error("end fucking game");
        }
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