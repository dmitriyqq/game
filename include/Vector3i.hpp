#pragma once

struct Vector3i{
    int x;
    int y;
    int z;

    bool operator==(const Vector3i &other){
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    friend bool operator<(Vector3i a, Vector3i b){
        return a.x < b.x ? true:
               a.y < b.y ? true:
               a.z == b.z ? true : false;
    }
};