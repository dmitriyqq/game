#pragma once

struct Vector3i{
    int x;
    int y;
    int z;

    bool operator==(const Vector3i &other){
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    friend bool operator<(const Vector3i &a, const Vector3i &b){
        if( a.x < b.x ) {
            return true;
        }else if( a.x == b.x){
            if(a.y < b.y){
                return true;
            }else if(a.y == b.y){
                if(a.z < b.z){
                    return true;
                }
            }
        }

        return false;
    }
};