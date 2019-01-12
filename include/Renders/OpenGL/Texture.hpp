#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <glad/glad.h>
#include <stb_image.hpp>
#include <iostream>

class Texture{
    unsigned int __id;
    int __width, __height;
    int __numChannels;
public:
    std::string type;
    std::string path;
    Texture() = default;
    Texture(const Texture &texture) = default;
    explicit Texture(const std::string & filename){
        path = filename;
        load(filename);
    }

    void load(const std::string & filename){
        unsigned char *data = stbi_load(filename.c_str(), &__width, &__height, &__numChannels, 0);
        if (data){
            glGenTextures(1, &__id);
            glBindTexture(GL_TEXTURE_2D, __id);

            if(__numChannels == 4) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, __width, __height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            } else if(__numChannels == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, __width, __height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }

            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }else{
            std::cout << "Failed to load texture" << std::endl;
        }
    }

    unsigned int getId() const {
        return __id;
    }

    void use() const {
        glBindTexture(GL_TEXTURE_2D, __id);
    }

    ~Texture(){
        // glDeleteTextures(1, &__id);
    }
};