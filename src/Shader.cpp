#include <fstream>
#include <iostream>

#include <glad/glad.h>

#include "Renders/OpenGL/Shader.hpp"

namespace OpenGL {

    using std::ifstream;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios;

    unsigned long getFileLength(ifstream &file);

    Shader::Shader(string const &filename, GLenum shaderType) {
        string source = getSource(filename);
        m_id = glCreateShader(shaderType);

        const GLchar *src = source.c_str();

        glShaderSource(m_id, 1, &src, NULL);
        glCompileShader(m_id);

        //Error checking
        int success;
        char infoLog[512];
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_id, 512, NULL, infoLog);
            cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << endl;
        } else {
            cout << "Succsesfully load shader" << endl;
        }
    }

    Shader::~Shader() {
        glDeleteShader(m_id);
    }

    string Shader::getSource(string const &filename) {
        ifstream file;
        file.open(filename.c_str(), ios::in);
        if (!file) {
            printf("Couldn't open file!");
        }

        int len = getFileLength(file);
        char *shaderSource;
        shaderSource = new char[len + 1];

        unsigned int i = 0;
        while (file.good()) {
            shaderSource[i] = file.get();
            if (!file.eof())
                i++;
        }

        shaderSource[i] = 0;

        file.close();
        return string(shaderSource);
    }

    unsigned long getFileLength(ifstream &file) {
        if (!file.good()) return 0;

        unsigned long pos = file.tellg();
        file.seekg(0, ios::end);
        unsigned long len = file.tellg();
        file.seekg(ios::beg);

        return len;
    }

}