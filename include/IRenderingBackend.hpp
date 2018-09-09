#pragma once

#include <iostream>

#include <curses.h>
#include <spdlog/spdlog.h>

#include "Voxel.hpp"

class IRenderingBackend
{

  public:
  virtual void display(const Voxel &voxel, int y, int x) const = 0;
};

class NCursesRenderingBackend : public IRenderingBackend
{
    void init()
    {
        initscr();

        box(stdscr,'*','*');
        refresh();
    }

  public:
    NCursesRenderingBackend(){
        init();
    }

    ~NCursesRenderingBackend(){
        endwin();
    }

    void display(const Voxel &voxel, int y, int x) const override
    {
        auto logger = spdlog::get("main_logger");

        logger->debug("Drawing voxel at {0}, {1}, {2}", voxel.position.x, voxel.position.y, voxel.position.z);

        mvaddch(y, x, voxel.type == Voxel::Type::BLOCK ? '#' : '_');
    }
};