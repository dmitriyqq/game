#ifndef SHADER_H
#define SHADER_H

namespace OpenGL{

#include <string>
#include <glad/glad.h>

using std::string;

class Shader{
    public:
        Shader(string const& filename, GLenum shaderType);
        unsigned int getId() const { return m_id;}
        virtual ~Shader();
    private:
        string getSource(string const& filename);
        unsigned int m_id;
};

}

#endif // SHADER_H
