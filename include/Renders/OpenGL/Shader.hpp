#pragma once

namespace OpenGL{

#include <string>
#include <glad/glad.h>

class Shader{
    public:
        Shader(std::string const& filename, GLenum shaderType);
        unsigned int getId() const { return m_id;}
        virtual ~Shader();
    private:
        std::string getSource(std::string const& filename);
        unsigned int m_id;
};

}
