#include <iostream>

#include <Engine/Game.hpp>
#include <SnakeRenderer.hpp>
#include <Renders/OpenGL/Camera.hpp>
#include <Engine/IUpdatable.hpp>

#include "CellFactory.hpp"
#include "Snake.hpp"
#include "SnakeBonus.hpp"
#include "Wall.hpp"
#include <Engine/IUpdatable.hpp>

class Game : public Engine::IGame {
    // UiT __ui;

    Snake __snake;
    // GameEnd __game_end;
    SnakeRenderer *__renderer;
    CellsFactory *__factory;
    std::vector <IDrawable*> drawables;
    Glfw::InputManager *__iomanager;
    void update() override {
//        keytable.update();
        if(__ticks%10 == 0)
            __snake.move();
        if(__factory->updateCells(__snake)){
            __playing = false;
        }

        __renderer->update(__delta_time);
    }

    void draw() const override {
        __renderer->display(drawables);
    }

public:
    Game(){
//        keytable.addSubscriber(&__game_end);
        __renderer = new SnakeRenderer(__iomanager);
        __iomanager->addSubscriber((Engine::Input::IKeyboardSubscriber*)&__snake);
        drawables.push_back(&__snake);
        __factory = new CellsFactory(__renderer->width(), __renderer->height());
        auto c =__factory->getCells();
        for(auto cell: c){
            drawables.push_back(cell.second);
        }

    }
};


int main(){
    Game game;
    game.start();
}