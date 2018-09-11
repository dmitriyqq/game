#pragma once

#include <array>
#include <curses.h>
#include <spdlog/spdlog.h>

class KeyTable{
    std::array<bool, 256> _table;

public:
    bool isPressed(char key){
        return _table[(unsigned char) key];
    }

    void release(char key){
        _table[(unsigned char) key] = false;
    }

    void press(char key){
        _table[(unsigned char) key] = true;
    }

    void update(){
        auto logger = spdlog::get("main_logger");
        char c = getch();
        if(c != ERR){
            press(c);
            logger->warn("{} is pressed", c);
        }
    }
};