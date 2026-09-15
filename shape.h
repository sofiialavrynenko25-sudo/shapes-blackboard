#pragma once

#include <string>
#include <vector>

class Shape 
{
    protected:
        int _id;
        int _x;
        int _y;
        std::string _color;
        bool _isFilled;
        
    public:
        Shape(int id, int x, int y, const std::string& color, bool isFilled)
            : _id(id), _x(x), _y(y), _color(color), _isFilled(isFilled) {}

        virtual bool CheckCoordinates(int x, int y) const = 0;

        virtual void DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const = 0;

        virtual void EditParameters() = 0;

        virtual std::string ToString() const = 0;

        virtual std::string GetType() const = 0;

        int GetId() const;

        int GetX() const;

        int GetY() const;

        std::string GetColor() const;

        bool GetIsFilled() const;

        void SetParameters(int newX, int newY);
        
        void SetColor(const std::string& newColor);
        
        void SetFilled(bool newIsFilled);

        virtual ~Shape() = default;
};