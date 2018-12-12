#pragma once

#include <Engine/IUpdatable.hpp>
#include <Engine/IMouseSubscriber.hpp>
#include "./Camera.hpp"

namespace OpenGL{

class FpsLikeCamera: public Camera, public Engine::Input::IUpdatable, public Engine::Input::IMouseSubscriber {
        float __speed = 0.010f;
    public:
        FpsLikeCamera(): Camera() {}
        void update(float delta_time, Engine::Input::IKeyboardState &keyboard) override {

            if(keyboard.isKeyPressed(Engine::Input::Key::UP)){
                setPosition(Direction::FORWARD, __speed * delta_time);
            }

            if(keyboard.isKeyPressed(Engine::Input::Key::DOWN)){
                setPosition(Direction::BACKWARD, __speed * delta_time);
            }

            if(keyboard.isKeyPressed(Engine::Input::Key::LEFT)){
                setPosition(Direction::LEFT, __speed * delta_time);
            }

            if(keyboard.isKeyPressed(Engine::Input::Key::RIGHT)){
                setPosition(Direction::RIGHT, __speed * delta_time);
            }

        }

        void update(double x, double y, double dx, double dy) override {
            setView(-dx, dy, true);
        }
    };

}
