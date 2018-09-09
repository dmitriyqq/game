#include <iostream>
#include "Camera.hpp"
#include "VoxelSpace.hpp"
#include "ISpaceGenerator.hpp"

template< typename SpaceT, typename CameraT >
class Game{
    SpaceT _space;
    CameraT _camera;

public:
    Game(){
        auto logger = spdlog::get("main_logger");
        logger->info("Creating Game");

        auto generator = new PerlynSpaceGenerator();
        generator->generate(_space, 100, 100, 100);
    }

    void update(){
        // std::cout<<"update"<<std::endl;
        char c = getch();
        if( c == 'q'){
            // TODO fix this
            throw "EXITFUCKINGGAME";
        }
    }

    void draw(){
        _camera.display(&_space);
    }

};

int main(){
    auto logger = spdlog::basic_logger_mt("main_logger", "log.txt");
    logger->error("Welcome to spdlog!");
    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::debug);

    try {
        auto myGame = new Game<SimpleSpace, Camera>();
        while(true) {
            myGame->draw();
            myGame->update();
        }
    }
    catch (std::exception & e){
        logger->error("exception_occured " + std::string(e.what()));
        logger->flush();
        // TODO fix this
        endwin();

        return 23;
    }
    //getch();
    endwin();
    return 0;
}