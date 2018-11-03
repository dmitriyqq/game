#pragma once

#include "SnakeBonus.hpp"
#include "Wall.hpp"
#include "Snake.hpp"

#include <map>
#include <random>
#include <ctime>


using std::map;
using std::pair;

class CellsFactory{
    std::map <std::pair<int, int>, SnakeBonus*> bonuses;
    int __maxX;
    int __maxY;
public:
    CellsFactory(int maxX, int maxY): __maxX(maxX), __maxY(maxY) {
        for(int i = 0; i < 5; i++){
            auto coords = getNewCellCords();
            bonuses[coords] = new SnakeBonus(coords.first, coords.second);
        }
        for(int i = 0; i < 25; i++){
            auto coords = getNewCellCords();
            bonuses[coords] = new Wall(coords.first, coords.second);
        }

        for(int i = 0; i < __maxX; i++){
            std::pair<int, int> coordsTop = {i, 0};
            std::pair<int, int> coordsBot = {i, __maxY-1};
            bonuses[coordsTop] = new Wall(coordsTop.first, coordsTop.second);
            bonuses[coordsBot] = new Wall(coordsBot.first, coordsBot.second);
        }

        for(int i = 0; i < __maxY; i++){
            std::pair<int, int> coordsTop = {0, i};
            std::pair<int, int> coordsBot = {__maxX-1, i};
            bonuses[coordsTop] = new Wall(coordsTop.first, coordsTop.second);
            bonuses[coordsBot] = new Wall(coordsBot.first, coordsBot.second);
        }
    }


    bool updateCells(Snake &snake){
        for(auto &bonus: bonuses){
            auto resp = bonus.second->isEaten(snake);
            if(resp.second){
                return true;
            }

            if(resp.first){
                auto coords = getNewCellCords();
                bonus.second->recreate(coords.first, coords.second);
            }
        }

        return false;
    }

    std::map<std::pair<int, int>, SnakeBonus* >& getCells(){
        return bonuses;
    }

    std::pair<int, int> getNewCellCords(int seed = -1){
        static std::mt19937 generator((unsigned int) time(nullptr));
        static std::uniform_int_distribution<int> distributionX(1, __maxX-1);
        static std::uniform_int_distribution<int> distributionY(1, __maxY-1);
        if(seed != -1) generator.seed(seed);
        std::pair<int, int> coords(distributionX(generator), distributionY(generator));
        while(bonuses.find(coords) != end(bonuses)){
            coords.first = distributionX(generator);
            coords.second = distributionY(generator);
        }
        return coords;
    }
};

