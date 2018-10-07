#pragma once

#include <chrono>
#include "Utils/Constants.hpp"
#include "Renders/Console/DebugWindow.hpp"
#include "Renders/Console/UI.hpp"

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
            while(__playing) {
                // auto logger = spdlog::get(Constants::LOOP_LOGGER);
                auto newTime = std::chrono::system_clock::now();
                float delta = (std::chrono::duration_cast<std::chrono::milliseconds>(newTime - __last_time).count() /
                               1000.0f);

                __logic_deltatime += delta;
                __render_deltatime += delta;

                if (__logic_deltatime > __desired_logic_deltatime) {
                    __logic_deltatime = 0;
                    update();
                    __ticks++;
                }

                if (__render_deltatime > __desired_render_deltatime) {
                    __render_deltatime = 0;
                    draw();
                }

                __last_time = newTime;
                __delta_time = __render_deltatime;
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds(1));
            //            if (__playing) {
            //                gameLoop();
            //            }
        }

    public:

        IGame() {
            // auto logger = spdlog::basic_logger_mt(Constants::LOOP_LOGGER, "log.txt");
        }
        virtual void start() {
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
        int __ticks = 0;
        float __delta_time = 0.0f;
    };

}