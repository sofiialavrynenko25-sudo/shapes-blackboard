#pragma once

#include <memory>
#include <vector>
#include "shape.h"

class Board 
{
    private:
        int _height;
        int _width;
        std::vector<std::unique_ptr<Shape>> _shapes;
        int _selected;
    
    public:
        Board(int width, int height)
            :_width(width), _height(height), _selected(-1) {}

        void Draw() const;

        void AddShape(std::unique_ptr<Shape> shape);

        bool SelectShape(int id);

        bool SelectShapeCoord(int x, int y);

        void RemoveSelected();

        void MoveSelected(int newX, int newY);

        void SaveToFile(const std::string& filename) const;

        void LoadFromFile(const std::string& filename);

        void Clear();

        const std::vector<std::unique_ptr<Shape>>& GetShapes() const;

        Shape* GetSelected() const;

        int GetWidth();

        int GetHeight();

        ~Board();
};