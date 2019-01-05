#pragma once

#include <iostream>

#include <Curses.h>
#include <spdlog/spdlog.h>

#include "Voxel.hpp"

class IRenderingBackend
{

  public:

    virtual int width() = 0;

    virtual int height() = 0;

    virtual void startDisplay() = 0;

    virtual void display(const Voxel &voxel, int y, int x) const = 0;

    virtual void endDisplay() = 0;
};

class NCursesRenderingBackend : public IRenderingBackend
{
    WINDOW* window;


  public:
    int width() override {
        int y, x;
        getmaxyx(window, y, x);
        return x;
    }

    int height() override {
        int y, x;
        getmaxyx(window, y, x);
        return y;
    }

    NCursesRenderingBackend(int width, int height){
        auto logger = spdlog::get("main_logger");
        logger->info("NCursesRenderingBackend: Width: {}, Height: {}", width, height);
        window = newwin(height, width, 0, 0);
        box(window, '|', '-');
        // wrefresh(window);
    }

    ~NCursesRenderingBackend(){
        endwin();
    }

    void startDisplay() override {
        wclear(window);
        for(int i = 0; i < width(); i++){
            for(int j = 0; j < height(); j++){
                mvaddch(j, i, ' ');
            }
        }
    }

    void endDisplay() override{
        wnoutrefresh(window);
    }

    void display(const Voxel &voxel, int y, int x) const override
    {
        // auto logger = spdlog::get("main_logger");

        // logger->debug("Drawing voxel at screen({}, {}) - model: ({}, {}, {})", x, y, voxel.position.x, voxel.position.y, voxel.position.z);

        start_color();  /* Start color */
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_WHITE, COLOR_BLACK);

        switch(voxel.type){
            case Voxel::Type::AIR:
                wattron(window, COLOR_PAIR(1));
                mvwaddch(window, y, x, '#');
                break;
            case Voxel::Type::WATER:
                wattron(window, COLOR_PAIR(2));
                mvwaddch(window, y, x, '~');
                break;
            case Voxel::Type::SAND:
                wattron(window, COLOR_PAIR(3));
                mvwaddch(window, y, x, '.');
                break;
            case Voxel::Type::GRASS:
                wattron(window, COLOR_PAIR(4));
                mvwaddch(window, y, x, '_');
                break;
            case Voxel::Type::ROCK:
                wattron(window, COLOR_PAIR(5));
                mvwaddch(window, y, x, '#');
                break;
            case Voxel::Type::SNOW:
                wattron(window, COLOR_PAIR(6));
                mvwaddch(window, y, x, '*');
                break;
        }
    }
};