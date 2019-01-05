#pragma once
#include "TextureAtlasVAO.hpp"

class Sprite {
    TextureAtlasVAO * __atlas;
    int __offset;
    public:
        Sprite(TextureAtlasVAO * atlas, int offset)
        : __atlas(atlas), __offset(offset) {

        }

        void draw() {
            __atlas->draw(__offset);
        }
};