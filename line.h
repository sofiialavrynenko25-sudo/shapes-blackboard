#pragma once

#include "shape.h"

class Line : public Shape
{
    private:
        int _length;
        bool _isVertical;
    
    public:
        Line(int id, int x, int y, int length, bool isVertical, const std::string& color)
            : Shape(id, x, y, color, false), _length(length), _isVertical(isVertical) {}

        bool CheckCoordinates(int x, int y) const override;

        virtual void DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const override;

        virtual void EditParameters() override;

        virtual std::string ToString() const override;

        virtual bool IsEqual(const Shape* other) const override;

        std::string GetType() const override;

        int GetLength() const;

        bool GetIsVertical() const;
};