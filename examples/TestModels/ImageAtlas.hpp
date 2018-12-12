#pragma once

#include <fstream>
#include <vector>

#include <Renders/OpenGL/Texture.hpp>
#include <nlohmann/json.hpp>

#include "TextureAtlasVAO.hpp"
#include "Sprite.hpp"

using json = nlohmann::json;

class ImageAtlas {
    Texture *__texture;
    TextureAtlasVAO *__vao;

    int __height, __width;
    std::vector<Frame> __frames;
    std::map<std::string, int> __offsets;
public:
    ImageAtlas() {
        std::string str = "";
        std::string metafile_path = "./sharedAssets/spritesheets/sprites.json";
        std::string texture_path = "./sharedAssets/spritesheets/sprites.png";

        __texture = new Texture(texture_path);
        std::ifstream metafile(metafile_path);
        __texture->use();
        json meta;
        metafile>>meta;

        json metainfo = meta["meta"];

        json size = metainfo["size"];
        json w = size["w"];
        json h = size["h"];

        __height = h;
        __width = w;

        auto frames = meta["frames"];
        int i = 0;
        for (auto &&frame : frames) {
            std::string filename = frame["filename"];
            __offsets[filename] = i++;
            json offsets = frame["frame"];
            __frames.emplace_back(
                offsets["x"],
                offsets["y"],
                offsets["w"],
                offsets["h"],
                filename);
        }

        __vao = new TextureAtlasVAO(getFrames(), __width, __height, __texture->getId());
    }

    Sprite* getFrame(const std::string &filename) {
       int offset = __offsets[filename];
       return new Sprite(__vao, offset);
    }

    int getWidth() const { return __width; }

    int getHeight() const { return __height; }

    std::vector<Frame>& getFrames() {
        return __frames;
    }


};