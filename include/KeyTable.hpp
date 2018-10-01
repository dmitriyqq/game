#pragma once

#include <vector>

#include <Curses.h>
#include <spdlog/spdlog.h>
#include "UI.hpp"

class IKeyboardSubscriber{
public:
    virtual void processKey(char key) = 0;
};

class KeyTable{
    std::vector <IKeyboardSubscriber *> __subscribers;
public:
    void update(){
        auto logger = spdlog::get("main_logger");
        char c = getch();
        while(c != ERR){
            logger->warn("{} is pressed", c);

            std::string key;
            key += c;

            DebugWindow::debug("key", key);

            for(auto &subscriber: __subscribers){
                subscriber->processKey(c);
            }

            c = getch();
        }
    }

    void addSubscriber(IKeyboardSubscriber *subscriber){
        __subscribers.push_back(subscriber);
    }
};