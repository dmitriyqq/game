#pragma once

#include <iostream>

#include <curses.h>

#include "Voxel.hpp"

class IRenderingBackend
{

  public:
    void display(const Voxel &voxel) const;
};

class NCursesRenderingBackend
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

    void display(const Voxel &voxel) const
    {
        std::cout << "Drawing voxel at" << voxel.x << "" << voxel.y << "" << voxel.z << std::endl;
    }
};