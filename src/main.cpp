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
        auto generator = new PerlynSpaceGenerator();
        generator->generate(_space, 100, 100, 100);
    }

    void update(){
        std::cout<<"update"<<std::endl;
    }

    void draw(){
        _camera.display(&_space);
    }

};

int main(int argc, char** argv){
    auto myGame = new Game<SimpleSpace, Camera>();
    myGame->draw();

}