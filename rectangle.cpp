#include <cmath>
#include <iostream>
#include <sstream>
#include "rectangle.h"

std::string Rectangle::GetType() const
{
    return "rectangle";
}

int Rectangle::GetWidth() const
{
    return _width;
}

int Rectangle::GetHeight() const
{
    return _height;
}

bool Rectangle::CheckCoordinates(int x, int y) const
{
    int lowerLim = _y - _height / 2;
    int upperLim = _y + _height / 2;
    int rightLim = _x + _width / 2;
    int leftLim = _x - _width / 2;

    bool insideLims = (x >= leftLim && x <= rightLim && y <= upperLim && y >= lowerLim);
    
    if (!insideLims)
    {
        return false;
    }

    if (_isFilled)
    {
        return true;
    }
    
    bool onBorder = (x == leftLim || x == rightLim || y == upperLim || y == lowerLim);

    return onBorder;
}

void Rectangle::DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const
{
    int startY = std::max(0, _y - _height / 2);
    int endY = std::min(height - 1, _y + _height / 2);
    int startX = std::max(0, _x - _width / 2);
    int endX = std::min(width - 1, _x + _width / 2);

    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            if (CheckCoordinates(x, y))
            {
                grid[y][x] = _color.empty() ? '*' : _color[0];
            }
        }
    }
}

bool Rectangle::EditParameters(std::stringstream& ss, int boardWidth, int boardHeight)
{
    int newWidth, newHeight;

    if (!(ss >> newWidth >> newHeight) || newWidth <= 0 || newHeight <= 0)
    {
        return false;
    }

    if (newWidth >= boardWidth || newHeight >= boardHeight)
    {
        std::cout << "Shape cannot be bigger than a board.\n";
        return false;
    }

    _width = newWidth;
    _height = newHeight;
    return true;
}

std::string Rectangle::Serialize() const
{
    std::ostringstream toReturn;

    toReturn << GetType() << " "
            << _id << " "
            << _x << " "
            << _y << " "
            << _width << " "
            << _height << " "
            << _color << " "
            << _isFilled;
        
    return toReturn.str();
}

bool Rectangle::Deserialize(std::istream& serialized)
{
    if (!(serialized >> _id >> _x >> _y >> _width >> _height >> _color >> _isFilled))
    {
        return false;
    }

    return true;
}

std::string Rectangle::ToString() const
{
    std::string fill;

    if (_isFilled)
    {
        fill = "yes";
    }
    else
    {
        fill = "no";
    }

    return "Type: " + GetType() +
            " | ID " + std::to_string(_id) +
            " | Width: " + std::to_string(_width) +
            " | Height: " + std::to_string(_height) +
            " | Position: (" + std::to_string(_x) + ", " + std::to_string(_y) + ")" +
            " | Color: " + _color +
            " | Filled: " + fill;
}

bool Rectangle::IsEqual(const Shape* other) const
{
    if (other == nullptr || GetType() != other -> GetType())
    {
        return false;
    }

    const Rectangle* rectangle = dynamic_cast<const Rectangle*>(other);

    if (rectangle && _x == rectangle -> _x && _y == rectangle -> _y &&
        _width == rectangle -> _width && _height == rectangle -> _height && 
        _color == rectangle -> _color && _isFilled == rectangle -> _isFilled)
    {
        return true;
    }
    else
    {
        return false;
    }
}