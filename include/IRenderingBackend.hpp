#pragma once

#include <iostream>

#include <curses.h>
#include <spdlog/spdlog.h>

#include "Voxel.hpp"

class IRenderingBackend
{

  public:

    virtual int width() = 0;

    virtual int height() = 0;

    virtual void display(const Voxel &voxel, int y, int x) const = 0;
};

class NCursesRenderingBackend : public IRenderingBackend
{
    void init()
    {
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, 1);
        nodelay(stdscr, 0);

        auto logger = spdlog::get("main_logger");
        if(has_colors() == FALSE)
        {	endwin();
            logger->error("Your terminal does not support color");
            exit(1);
        }
        box(stdscr,'*','*');
        refresh();
    }

  public:
    int width() override {
        int y, x;
        getmaxyx(stdscr, y, x);
        return x;
    }

    int height() override {
        int y, x;
        getmaxyx(stdscr, y, x);
        return y;
    }

    NCursesRenderingBackend(){
        init();
    }

    ~NCursesRenderingBackend(){
        endwin();
    }

    void display(const Voxel &voxel, int y, int x) const override
    {
        auto logger = spdlog::get("main_logger");

        logger->debug("Drawing voxel at screen({}, {}) - model: ({}, {}, {})", x, y, voxel.position.x, voxel.position.y, voxel.position.z);

        start_color();  /* Start color */
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_WHITE, COLOR_BLACK);

        switch(voxel.type){
            case Voxel::Type::AIR:
                attron(COLOR_PAIR(1));
                mvaddch(y, x, '#');
                break;
            case Voxel::Type::WATER:
                attron(COLOR_PAIR(2));
                mvaddch(y, x, '~');
                break;
            case Voxel::Type::SAND:
                attron(COLOR_PAIR(3));
                mvaddch(y, x, '.');
                break;
            case Voxel::Type::GRASS:
                attron(COLOR_PAIR(4));
                mvaddch(y, x, '_');
                break;
            case Voxel::Type::ROCK:
                attron(COLOR_PAIR(5));
                mvaddch(y, x, '#');
                break;
            case Voxel::Type::SNOW:
                attron(COLOR_PAIR(6));
                mvaddch(y, x, '*');
                break;
        }

    }
};