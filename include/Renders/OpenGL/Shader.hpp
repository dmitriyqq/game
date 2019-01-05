#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>

namespace OpenGL{

class Shader{
    unsigned int m_id;

    std::string getSource(std::string const& filename){
        std::ifstream file;
        file.open(filename.c_str(), std::ios::in);
        if (!file) {
            printf("Couldn't open file!");
        }

        auto len = getFileLength(file);
        char *shaderSource;
        shaderSource = new char[len + 1];

        unsigned int i = 0;
        while (file.good()) {
            shaderSource[i] = (char) file.get();
            if (!file.eof())
                i++;
        }

        shaderSource[i] = 0;

        file.close();
        return std::string(shaderSource);
    }


    unsigned int getFileLength(std::ifstream &file) {
        if (!file.good()) return 0;

        // unsigned int pos = (unsigned int) file.tellg();
        file.seekg(0, std::ios::end);
        auto len = (unsigned int) file.tellg();
        file.seekg(std::ios::beg);

        return len;
    }

public:
    Shader(std::string const& filename, GLenum shaderType){
        std::string source = getSource(filename);
        m_id = glCreateShader(shaderType);

        const GLchar *src = source.c_str();

        glShaderSource(m_id, 1, &src, nullptr);
        glCompileShader(m_id);

        //Error checking
        int success;
        char infoLog[512];
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        } else {
            std::cout << "Succsesfully load shader" << std::endl;
        }
    }

    unsigned int getId() const {
        return m_id;
    }

    virtual ~Shader() {
        glDeleteShader(m_id);
    }
};

}
