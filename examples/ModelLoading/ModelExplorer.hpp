#pragma once

#include <Renders/OpenGL/Model.hpp>
#include <nanogui/nanogui.h>

class ModelExplorer: public nanogui::Widget {
public:
    ModelExplorer(nanogui::Widget *parent, OpenGL::Model *model): nanogui::Widget(parent){
        auto meshes = model->getMeshes();
        setLayout(new nanogui::GroupLayout());

        for (auto mesh : meshes) {
            auto str = "mesh v:" + std::to_string(mesh.getVertexCount())
                        + " i: " + std::to_string(mesh.getIndexCount())
                        + " t: " + std::to_string(mesh.getTexturesCount());
            new nanogui::Label(this, str);
        }
    }
};
