#pragma once

template <typename T>
struct Vector3{
    T x, y, z;

    Vector3 operator+=(const Vector3& other){
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    friend bool operator<(const Vector3& a, const Vector3& b){
        if(a.x < b.x){
            return true;
        }else if(a.x > b.x){
            return false;
        }else{
            if(a.y < b.y){
                return true;
            }else if(a.y > b.y){
                return false;
            }else{
                return (a.z < b.z);
            }
        }
    }
};

using Vector3i = Vector3<int>;