#pragma once

#include "shape.h"

class Rectangle : public Shape
{
    private:
        int _width;
        int _height;
    
    public:
        Rectangle(int id, int x, int y, int width, int height, const std::string& color, bool isFilled)
            : Shape(id, x, y, color, isFilled), _width(width), _height(height) {}

        bool CheckCoordinates(int x, int y) const override;

        virtual void DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const override;

        virtual void EditParameters() override;

        virtual std::string ToString() const override;

        std::string GetType() const override;

        int GetWidth() const;
        
        int GetHeight() const;
};