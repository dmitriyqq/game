#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <Engine/Game.hpp>
#include <Renders/OpenGL/Texture.hpp>


#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

class Model
{
public:
    /*  Functions   */
    Model(char *path)
    {
        loadModel(path);
    }
    void Draw(Engine::OpenGL::ShaderProgram shader);
private:
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);
};

class TestGame: public Engine::IGame {
public:
    TestGame() : Engine::IGame() {
        Assimp::Importer importer;
        std::string path = "./trees.obj";
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    }

    ~TestGame()


protected:
    void update() override {

    }

    void draw() const override {

    }
};

/* ---------------------------------------------------------------------------- */
int main(int argc, char **argv)
{
    TestGame game;
    game.start();
    return 0;
}