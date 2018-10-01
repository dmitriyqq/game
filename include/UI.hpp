#pragma once

#include "Camera.hpp"
#include "DebugWindow.hpp"

template <typename CameraT>
class UI {

    CameraT *camera;
    DebugWindow *window;

    void init()
    {
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, true);
        nodelay(stdscr, true);
        raw();
        noecho();

        auto logger = spdlog::get("main_logger");
        if(has_colors() == FALSE)
        {	endwin();
            logger->error("Your terminal does not support color");
            exit(1);
        }
        box(stdscr, '|', '-');
        refresh();
    }

public:
    UI(){
        init();
        int width, height;
        getmaxyx(stdscr, height, width);
        auto logger = spdlog::get("main_logger");

        logger->info("Width={}, Height={}", width, height);
        logger->info("DW={}, A={}", DebugWindow::WIDTH, width - DebugWindow::WIDTH);
        logger->info("Offset={}", width - DebugWindow::WIDTH);

        camera = new CameraT(width - DebugWindow::WIDTH, height);
        window = new DebugWindow(DebugWindow::getXOffset(width), height);
    }

    int gameWidth() const{
        return camera->width();
    }

    int gameHeight() const{
        return camera->height();
    }

    void display(std::vector <IDrawable *> drawables) const{

        DebugWindow::debug("width", camera->width());
        DebugWindow::debug("height", camera->height());

        camera->display(drawables);
        window->draw();
    }
};
