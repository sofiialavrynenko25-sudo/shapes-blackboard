#include <iostream>
#include "board.h"
#include "shape.h"

void Board::Draw() const
{
    std::vector<std::vector<char>> grid (_height, std::vector<char> (_width, ' '));
    
    for (const auto* shape : _shapes)
    {
        if (shape != nullptr)
        {
            shape -> DrawOnBoard(grid, _width, _height);
        }
    }

    std::cout << "=" << std::string(_width, '=') << "=\n";

    for (int y = 0; y < _height; y++)
    {
        std::cout << "|";

        for (int x = 0; x < _width; x++)
        {
            std::cout << grid[y][x];
        }

        std::cout << "|\n";
    }

    std::cout << "=" << std::string(_width, '=') << "=\n";
}

void Board::AddShape(Shape* shape)
{
    if (shape == nullptr)
    {
        std::cout << "Cannot add a non-existent shape.\n";
        return;
    }

    for (const auto* existShape : _shapes)
    {
        if (existShape -> GetId() == shape -> GetId())
        {
            std::cout << "Cannot add a shape with existing ID.\n";
            return;
        }
    }

    _shapes.push_back(shape);
    _selected = _shapes.size() - 1;

    std::cout << "Shape (" << shape -> GetType() << ") was added.\n";
}

bool Board::SelectShape(int id)
{
    if (_shapes.empty())
    {
        std::cout << "There no shapes added yet, cannot select.\n";
        return false;
    }

    for (int i = 0; i < _shapes.size(); i++)
    {
        if (_shapes[i] -> GetId() == id)
        {
            _selected = i;
            std::cout << "Shape with ID = " << id << " was selected.\n";
            return true;
        }
    }

    std::cout << "The shape with ID = " << id << " was not found.\n";
    return false;
}

void Board::RemoveSelected()
{
    if (_selected == -1)
    {
        std::cout << "Nothing is selected, cannot remove.\n";
        return;
    }

    delete _shapes[_selected];

    _shapes.erase(_shapes.begin() + _selected);

    _selected = _shapes.size() - 1;

    std::cout << "Selected shape was removed.\n"; 
}

void Board::MoveSelected(int newX, int newY)
{
    if (newX >= _width || newY >= _height || newX < 0 || newY < 0)
    {
        std::cout << "New coordinates are outside the board, cannot move.\n";
        return;
    }

    if (_selected == -1)
    {
        std::cout << "Nothing is selected, cannot move.\n";
        return;
    }

    Shape* shapeToMove = _shapes[_selected]; 
    shapeToMove -> SetParameters(newX, newY);

    _shapes.erase(_shapes.begin() + _selected);
    _shapes.push_back(shapeToMove);

    _selected = _shapes.size() - 1;

    std::cout << "Selected shape was moved.\n";
}

void Board::Clear()
{
    for (auto* shape : _shapes)
    {
        delete shape;
    }

    _shapes.clear();

    _selected = -1;

    std::cout << "Board was cleared.\n";
}

std::vector<Shape*> Board::GetShapes()
{
    return _shapes;
}

Board::~Board()
{
    Clear();
}