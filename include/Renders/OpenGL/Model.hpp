#pragma once

#include <Renders/OpenGL/ModelVAO.hpp>
#include <Renders/IDrawable.hpp>
#include <Renders/OpenGL/IBoundingBoxDrawable.hpp>
#include "BoundingBox.hpp"

#include <vector>
#include <utility>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

#include <spdlog/spdlog.h>

#include <glm/glm.hpp>

namespace OpenGL {

class Model : public IBoundingBoxDrawable
{
    std::vector<ModelVAO> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    OpenGL::ShaderProgram *__program = nullptr;
    std::string __directory;

    bool __draw_bounding_box = true;
    bool __bounding_box_calc = false;

    BoundingBox *__bounding_box = nullptr;

    glm::vec3 min;
    glm::vec3 max;

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if(std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if(!skip)
            {   // if texture hasn't been loaded already, load it
                Texture texture(__directory + "/" + str.C_Str());
                texture.type = typeName;
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }  
public:
    const std::vector<ModelVAO> & getMeshes() const {
        return meshes;
    }

    const std::vector<Texture> & getAllTextures() const {
        return textures_loaded;
    }

    ModelVAO processMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            // process vertex positions, normals and texture coordinates
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;

            if (!__bounding_box_calc) {
                max = min = vector;
                __bounding_box_calc = true;
            }

            // bounding box
            max.x = std::max(max.x, vector.x);
            max.y = std::max(max.y, vector.y);
            max.z = std::max(max.z, vector.z);

            min.x = std::min(min.x, vector.x);
            min.y = std::min(min.y, vector.z);
            min.z = std::min(min.z, vector.z);

            if (mesh->mNormals) {
                // normals
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }


            if(mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x; 
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoords = vec;
            }
            else
            {
                vertex.texCoords = glm::vec2(0.0f, 0.0f);
            }

            
            vertices.push_back(vertex);
        }
        // process indices
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process material
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
        return ModelVAO(vertices, indices, textures, __program);
    } 
  
    void processNode(aiNode *node, const aiScene *scene)
    {
        // process all the node's meshes (if any)
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
            meshes.push_back(processMesh(mesh, scene));
        }
        // then do the same for each of its children
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    } 

    void loadModel(const std::string &path)
    {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
        
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
        {
            auto logger = spdlog::get("log");
            logger->error("assimp error {}", import.GetErrorString());
            return;
        }

        processNode(scene->mRootNode, scene);
    }

    Model(const std::string &path, OpenGL::ShaderProgram *program)
    {
        __program = program;
        __directory = path.substr(0, path.find_last_of('/'));
        loadModel(path);
    }

    void draw() const
    {
        for(unsigned int i = 0; i < meshes.size(); i++){
            meshes[i].draw();
        }
    }  

    std::pair<glm::vec3, glm::vec3> getBox() const {
        glm::vec3 a = min, b = max;
        return std::make_pair(a, b);
    }
};

}