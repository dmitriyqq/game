#pragma once

#include <map>
#include <Curses.h>
#include <spdlog/spdlog.h>

class DebugWindow{
    static std::map <std::string, std::string> __debugKeyValue;
    static std::map <std::string, int> __count;

    WINDOW* window;

public:
    static constexpr int WIDTH = 30;

    static void debug(const std::string &key, const std::string &value){
        DebugWindow::__debugKeyValue[key] = value;
        DebugWindow::__count[key]++;
    }

    static void debug(const std::string &key, int value){
        DebugWindow::debug(key, std::to_string(value));
    }

    static void debug(const std::string &key, double value){
        DebugWindow::debug(key, std::to_string(value));
    }


    DebugWindow(int posx, int height){
        auto logger = spdlog::get("main_logger");
        logger->info("Debug Window: {} {} {} {}", height, WIDTH, 0, posx+1);
        window = newwin(height, WIDTH, 0, posx);
        box(window, '|', '-');
        wrefresh(window);
    }

    void draw(){
        int i = 1;
        for(auto &&debug: DebugWindow::__debugKeyValue){
            mvwprintw(window, i++, 1, "%s:%s", debug.first.c_str(), debug.second.c_str());
        }
        wrefresh(window);
    }

    static int getXOffset(int allSize){
        return allSize - WIDTH;
    }

};

std::map <std::string, int> DebugWindow::__count = std::map <std::string, int>();
std::map <std::string, std::string> DebugWindow::__debugKeyValue = std::map <std::string, std::string>();