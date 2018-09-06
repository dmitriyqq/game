#pragma once

struct Vector3i{
    int x;
    int y;
    int z;

    bool operator==(const Vector3i other){
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    bool operator<(const Vector3i other){
        return this->x < other.x ? true:
               this->y < other.y ? true: 
               this->z == other.z ? true : false;
    } 
};