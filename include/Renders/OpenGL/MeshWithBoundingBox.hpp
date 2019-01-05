#pragma once

#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/IBoundingBoxDrawable.hpp>
#include <Renders/OpenGL/BoundingBox.hpp>
#include <Renders/OpenGL/Graphics2D.hpp>
#include <Engine/ISelectable.hpp>
#include <Renders/OpenGL/Utils.hpp>

#include <vector>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

namespace OpenGL {

class MeshWithBoundingBox : public Mesh, public Engine::ISelectable {
    BoundingBox *__box;
    std::vector <glm::vec3> __vertices;
    PositionShaderProgram *__program;
    Rectangle *__rectangle;
protected:
    IBoundingBox *__box_data;

    void calculateVertices() {
        auto p = __box_data->getBox();
        glm::vec3 min = p.first, max = p.second;
        __vertices.clear();

        __vertices.emplace_back(min.x, min.y, max.z);
        __vertices.emplace_back(max.x, min.y, max.z);
        __vertices.emplace_back(max.x, max.y, max.z);
        __vertices.emplace_back(min.x, max.y, max.z);
        __vertices.emplace_back(min.x, min.y, min.z);
        __vertices.emplace_back(max.x, min.y, min.z);
        __vertices.emplace_back(max.x, max.y, min.z);
        __vertices.emplace_back(min.x, max.y, min.z);
    }
public: 
    MeshWithBoundingBox(PositionShaderProgram *program, IBoundingBoxDrawable *drawable):
        Mesh(program, drawable),
        __program(program),
        __box_data(drawable),
        __box(new BoundingBox(drawable))
    {
        calculateVertices();
        __rectangle = OpenGL::Graphics2D::get()->getRectangleWH(0, 0, 200, 80);
    }

    void draw() const override {
        Mesh::draw();
        __box->draw();
        // __rectangle->draw();
    }


    std::vector<glm::vec2> projectVertices() const {
        // this code assumes that the __program has camera, e.g. that setCamera had been called at least once
        // othewise we can not project vertices
        // it is not good but for now it is ok because we call this method only 'onclick'
        std::vector <glm::vec2> a;

        int width = __program->getWidth();
        int height = __program->getHeight();

        ICamera *cam = __program->getCamera();
        glm::mat4 model = getPositionMatrix();
        glm::mat4 view = cam->getViewMatrix();
        glm::mat4 projection = cam->getProjectionMatrix(
                      __program->getWidth(), __program->getHeight());
        
        // precalc matrix product
        auto t = projection * view * model;
        // t = glm::transpose(t);
        for (auto && v: __vertices) {
            auto tt = t * glm::vec4(v, 1.0f);
            a.emplace_back(width * (tt.x + 1.0f) / 2.0f, height * (tt.y + 1.0f) / 2.0f);    
        }

        return a;
    }

    bool isSelected(int x, int y) const override {
        // BASIC Algorithm
        // get min, max of box
        // restore all vertices
        // get matrices for projection
        // project all vertices
        auto projectedVertices = projectVertices();
        
        glm::vec2 min = projectedVertices[0];
        glm::vec2 max = projectedVertices[0];

        auto log = spdlog::get("log");
        // find min-max
        for(auto &&v: projectedVertices) {
            // log->info("Rect for select {} {} ", v.x, v.y);
            min = Utils::min(min, v);
            max = Utils::max(max, v);
        }

        // log->info("Rect for select {} {} {} {}", min.x, min.y, max.x, max.y);
        // log->info("mouse {} {}", x, y);
        __rectangle->initialize(min.x, min.y, max.x - min.x, max.y - min.y);
        
        // check if point is inside min-max rect
        return x >= min.x && x <= max.x && y >= min.y && y <= max.y;
    };

    bool isSelectedReactangle(int x, int y, int width, int height) const override {
        int x2 = x + width;
        int y2 = y + height;
        // BASIC Algorithm
        // get min, max of box
        // restore all vertices
        // get matrices for projection
        // project all vertices
        auto projectedVertices = projectVertices();
        // check if every vertex  is inside min-max rect
        for(auto &&v: projectedVertices) {
            if (v.x >= x && v.x <= x2 && v.y >= y && v.y <= y2) {
                return true;
            }
        }

        return false;
    }

};

}