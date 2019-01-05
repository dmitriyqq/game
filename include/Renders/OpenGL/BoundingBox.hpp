#pragma once

/**
 * \class BoundingBox
 *
 * \brief draws BoundingBox
 *
 * This class provides an geometry for box that fits
 * coordinates provided by IBoundingBox
 * 
 * \note it needs to fix resource release
 */

#include <Renders/IDrawable.hpp>
#include <Renders/OpenGL/CubeVAO.hpp>

namespace OpenGL{

class BoundingBox: public IDrawable {
    CubeVAO *__vao;
    IBoundingBox *__box;

    public:
        BoundingBox(IBoundingBox *box) :
            __box(box),
            __vao(new CubeVAO(box))
        {
        }

        void draw() const override {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            __vao->draw();
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
};

}