#pragma once

#include "shape.h"

class Circle : public Shape
{
    private:
        int _radius;
    
    public:
        Circle(int id, int x, int y, int radius, const std::string& color, bool isFilled)
            : Shape(id, x, y, color, isFilled), _radius(radius) {}
        
        bool CheckCoordinates(int x, int y) const override;

        virtual void DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const override;

        virtual bool EditParameters(std::stringstream& ss) override;

        virtual std::string ToString() const override;

        virtual bool IsEqual(const Shape* other) const override;

        std::string GetType() const override;

        int GetRadius() const;
};