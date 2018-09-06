#pragma once

#include <iostream>

#include <curses.h>

#include "Voxel.hpp"

class IRenderingBackend
{

  public:
  virtual void display(const Voxel &voxel) const = 0;
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

    void display(const Voxel &voxel) const override
    {
        std::cout << "Drawing voxel at" << voxel.position.x << "" << voxel.position.y << "" << voxel.position.z << std::endl;
    }
};