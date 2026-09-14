#include "shape.h"

int Shape::GetId() const
{
    return _id;
}

int Shape::GetX() const
{
    return _x;
}

int Shape::GetY() const
{
    return _y;
}

std::string Shape::GetColor() const
{
    return _color;
}

bool Shape::GetIsFilled() const
{
    return _isFilled;
}

void Shape::SetParameters(int newX, int newY)
{
    _x = newX;
    _y = newY;
}

void Shape::SetColor(const std::string& newColor)
{
    _color = newColor;
}