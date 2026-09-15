#pragma once

#include "shape.h"

class Triangle : public Shape
{
    private:
        int _side;
    
    public:
        Triangle(int id, int x, int y, int side, const std::string& color, bool isFilled)
            : Shape(id, x, y, color, isFilled), _side(side) {}

        bool CheckCoordinates(int x, int y) const override;

        virtual void DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const override;

        virtual void EditParameters() override;

        virtual std::string ToString() const override;

        virtual bool IsEqual(const Shape* other) const override;

        std::string GetType() const override;

        int GetSide() const;
};