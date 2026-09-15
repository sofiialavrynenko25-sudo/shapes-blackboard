#pragma once

#include <vector>
#include "shape.h"

class Board 
{
    private:
        int _height;
        int _width;
        std::vector<Shape*> _shapes;
        int _selected;
    
    public:
        Board(int width, int height)
            :_width(width), _height(height), _selected(-1) {}

        void Draw() const;

        void AddShape(Shape* shape);

        bool SelectShape(int id);

        void RemoveSelected();

        void MoveSelected(int newX, int newY);

        void Clear();

        std::vector<Shape*> GetShapes();

        Shape* GetSelected();

        ~Board();
};