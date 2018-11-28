#pragma once

#include <vector>
#include <iostream>

#include "Voxel.hpp"
#include "ISpace.hpp"
#include <Renders/OpenGL/CubeMesh.hpp>

class ChunkMesh : public OpenGL::CubeMesh {
    ISpace *__rawdata = nullptr;
    static constexpr int CHUNK_SIZE = 16;
    static constexpr int CHUNK_HEIGHT = 16;
    int __chunkPositionX, __chunkPositionY;
    unsigned int __vao;
    unsigned int __vbuffer;
    unsigned int __numblocks = 0;

    void generateVAO(){
        __numblocks = 0;
        std::vector <float> verticies;
        for(int i = 0; i < CHUNK_SIZE; i++){
            for(int j = 0; j < CHUNK_SIZE; j++){
                for(int k = 0; k < CHUNK_HEIGHT; k++){
                    Vector3i vp = {i+__chunkPositionX*CHUNK_SIZE, k, j+__chunkPositionY*CHUNK_SIZE};
                    auto voxel = __rawdata->get(vp);
                    if(voxel.type != Voxel::Type::AIR){
                        __numblocks++;
                        float sz  = 1.0f / CHUNK_SIZE;
                        generateCubeVAO((float)i*sz+sz/2, (float)k*sz+sz/2, (float)j*sz+sz/2, sz, verticies);
                    }

                }
            }
        }
        if(!__numblocks){
            return;
        }

        //VAO
        glGenVertexArrays(1, &__vao);
        glBindVertexArray(__vao);
        //VBO
        glGenBuffers(1, &__vbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, __vbuffer);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(verticies[0]), &verticies[0], GL_STATIC_DRAW);
        std::cout<<__numblocks<<std::endl;
        std::cout<<(verticies.size() / 6 / __numblocks)<<std::endl;
        //position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);
        glEnableVertexAttribArray(0);
        //normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //Unbind
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

public:
    ChunkMesh(ISpace *data, int posx, int posy) : CubeMesh(), __chunkPositionX(posx), __chunkPositionY(posy)
    {
        __rawdata = data;
        setColor(0.5, 0.9, 0.9);
        generateVAO();
        setPosition(__chunkPositionX, 0, __chunkPositionY);
    }

    void useData(ISpace *c){
        __rawdata = c;
    }

    void draw(IWindow *window) const override{
        if(!__numblocks) return;
        __shaderProgram->setMat4("model", __model);
        glBindVertexArray(__vao);
        __shaderProgram->use();
        glDrawArrays(GL_TRIANGLES, 0, 36 * __numblocks);
    }

};