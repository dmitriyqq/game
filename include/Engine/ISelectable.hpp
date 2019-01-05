#pragma once

namespace Engine{

class ISelectable {
    public: 
        virtual bool isSelected(int x, int y) const = 0;

        virtual bool isSelectedReactangle(int x, int y, int width, int height) const = 0;
};

}