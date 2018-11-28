#define GLFW_INCLUDE_NONE
#include "../include/Game.hpp"

int main(){
    Game game;
    std::cout<<"Created game"<<std::endl;
    game.start();
    return 0;
}