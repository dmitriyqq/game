#pragma once

#include <map>
#include <curses.h>

class DebugWindow{
    static constexpr int WIDTH = 12;

    std::map <std::string, std::string> __debugKeyValue;
    std::map <std::string, int> __count;

    WINDOW* window;
public:
    void debug(const std::string &key, const std::string &value){
        __debugKeyValue[key] = value;
        __count[key]++;
    }

    DebugWindow(int posx, int height){
        window = newwin(0, posx, WIDTH, height);
    }

    void draw(){
        int i = 0;
        for(auto &&debug: __debugKeyValue){
            mvwprintw(window, i++, 0, "%s:%s", debug.first.c_str(), debug.second.c_str());
        }
        wrefresh(window);
    }

    static int getXOffset(int allSize){
        return allSize - WIDTH;
    }

};