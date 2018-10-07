#pragma once

struct Vector3f{
    float x;
    float y;
    float z;

    Vector3f operator+=(const Vector3f& other){
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }
};