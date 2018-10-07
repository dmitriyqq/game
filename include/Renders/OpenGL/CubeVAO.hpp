#pragma once

namespace OpenGL {

class CubeVAO {
public:
    CubeVAO();

    virtual ~CubeVAO();

    void draw();

    unsigned int getId() const { return m_id; }

private:
    unsigned int m_id;
    unsigned int myBuffer, myElemBuffer;
};

}
