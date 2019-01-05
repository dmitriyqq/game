#pragma once

#include <chrono>
#include <iostream>
#include "Utils/Constants.hpp"

namespace Engine {

    class IGame {
        std::chrono::system_clock::time_point __last_time;

        float __desired_logic_fps = 60.0f;
        float __desired_render_fps = 60.0f;

        float __desired_logic_deltatime = 1.0f / __desired_logic_fps;
        float __desired_render_deltatime = 1.0f / __desired_render_fps;

        float __logic_deltatime = 0.0f, __render_deltatime = 0.0f;

    protected:
        bool __playing = false;
        virtual void update() = 0;

        virtual void draw() const = 0;

        void gameLoop() {
            std::cout<<"game started"<<std::endl;
            while(__playing) {

                auto newTime = std::chrono::system_clock::now();
                float delta = std::chrono::duration_cast<std::chrono::milliseconds>
                        (newTime - __last_time).count() / 1000.0f;

                __logic_deltatime += delta;
                __render_deltatime += delta;

            //    if (__logic_deltatime > __desired_logic_deltatime) {
                //    __logic_deltatime = 0;
                    update();
                    __ticks++;
            //    }

            //    if (__render_deltatime > __desired_render_deltatime) {
                //    __render_deltatime = 0;
                    draw();
            //    }

                __last_time = newTime;
                __delta_time = __render_deltatime;
            }
        }

    public:
        virtual  ~IGame() = default;
        virtual void start() {
            std::cout<<"Starting game"<<std::endl;
            __last_time = std::chrono::system_clock::now();
            __playing = true;
            gameLoop();
        }

        virtual void finish() {
            __playing = false;
        }

        virtual void pause() {
            __playing = false;
        }

        // !TODO make this private and provide separate delta time to different stages
        int __ticks = 0;
        float __delta_time = 0.01f;
    };

}