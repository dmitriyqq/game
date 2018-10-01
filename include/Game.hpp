#pragma once

#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"

#include "Constants.hpp"
#include "DebugWindow.hpp"
#include "UI.hpp"

class IGame{
    std::chrono::system_clock::time_point __last_time;

    int __ticks = 0;

    float __desired_logic_fps = 10.0f;
    float __desired_render_fps =  10.0f;

    float __desired_logic_deltatime = 1.0f / __desired_logic_fps;
    float __desired_render_deltatime = 1.0f / __desired_render_fps;

    float __logic_deltatime = 0.0f, __render_deltatime = 0.0f;
protected:
    bool __playing = false;
protected:
    virtual void update() = 0;
    virtual void draw() const = 0;

    void gameLoop(){
        auto logger = spdlog::get(Constants::LOOP_LOGGER);
        // logger->info("game loop {} {}", __logic_deltatime, __render_deltatime);
        auto newTime = std::chrono::system_clock::now();
        float delta = (std::chrono::duration_cast<std::chrono::milliseconds>(newTime - __last_time).count() / 1000.0f);
        // logger->info("Delta={}", delta);

        __logic_deltatime += delta;
        __render_deltatime += delta;

        DebugWindow::debug("delta_time", delta);
        DebugWindow::debug("fps", 1.0f/delta);
        DebugWindow::debug("ticks", __ticks);
        DebugWindow::debug("dlogic", __desired_logic_deltatime);
        DebugWindow::debug("drender", __desired_render_deltatime);
        DebugWindow::debug("renderdt", __render_deltatime);
        DebugWindow::debug("logicdt", __logic_deltatime);

        if(__logic_deltatime > __desired_logic_deltatime) {
            __logic_deltatime = 0;
            logger->info("update");
            update();
            __ticks++;
            logger->info("end update");
        }

        if(__render_deltatime > __desired_render_deltatime){
            __render_deltatime = 0;
            logger->info("draw");
            draw();
            logger->info("end draw");
        }

        __last_time = newTime;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(__playing) {
            gameLoop();
        }
    }

public:
    IGame(){
        auto logger = spdlog::basic_logger_mt(Constants::LOOP_LOGGER, "log.txt");
        logger->error("Constructing game class!");
        logger->set_level(spdlog::level::debug);
        logger->flush_on(spdlog::level::info);
    }

    virtual void start(){
        __last_time = std::chrono::system_clock::now();
        auto logger = spdlog::get("main_logger");
        logger->info("starting Game");

        __playing = true;
        gameLoop();
    }

    virtual void finish(){
        __playing = false;
    }

    virtual void pause(){
        __playing = false;
    }
};
