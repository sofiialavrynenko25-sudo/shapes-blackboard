#include <iostream>
#include <fstream>
#include <string>
#include "board.h"
#include "shape.h"
#include "circle.h"
#include "triangle.h"
#include "line.h"
#include "rectangle.h"

void Board::Draw() const
{
    std::vector<std::vector<char>> grid (_height, std::vector<char> (_width, ' '));
    
    for (const auto& shape : _shapes)
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

void Board::AddShape(std::unique_ptr<Shape> shape)
{
    if (shape == nullptr)
    {
        std::cout << "Cannot add a non-existent shape.\n";
        return;
    }

    for (const auto& existShape : _shapes)
    {
        if (existShape -> GetId() == shape -> GetId())
        {
            std::cout << "Cannot add a shape with existing ID.\n";
            return;
        }

        if (existShape -> IsEqual(shape.get()))
        {
            std::cout << "Cannot add a shape with the same type and parameters.\n";
            return;
        }
    }

    _shapes.push_back(std::move(shape));
    _selected = _shapes.size() - 1;

    std::cout << "Shape was added.\n";
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

bool Board::SelectShapeCoord(int x, int y)
{
    for (int i = 0; i < _shapes.size(); i++)
    {
        if (_shapes[i] -> CheckCoordinates(x, y))
        {
            _selected = i;
            std::cout << "Shape with ID = " << _shapes[i] -> GetId() << " was selected.\n";
            return true;
        }
    }

    std::cout << "No shape found at coordinates (" << x << ", " << y << ").\n";
    return false;
}

void Board::RemoveSelected()
{
    if (_selected == -1)
    {
        std::cout << "Nothing is selected, cannot remove.\n";
        return;
    }

    _shapes.erase(_shapes.begin() + _selected);

    if (_shapes.empty())
    {
        _selected = -1;
    }
    else
    {
        _selected = _shapes.size() - 1;
    }

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

    _shapes[_selected] -> SetParameters(newX, newY);
    std::unique_ptr<Shape> shapeToMove = std::move(_shapes[_selected]); 

    _shapes.erase(_shapes.begin() + _selected);
    _shapes.push_back(std::move(shapeToMove));

    _selected = _shapes.size() - 1;

    std::cout << "Selected shape was moved.\n";
}

void Board::SaveToFile(const std::string& filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Cannot open the file.\n";
        return;
    }

    file << _width << " " << _height << "\n";

    for (const auto& shape : _shapes)
    {
        if (shape != nullptr)
        {
                file << shape -> Serialize() << "\n";
        }
    }

    file.close();
    std::cout << "Board saved.\n";
}

void Board::LoadFromFile(const std::string& filename)
{
    bool error = false;
    std::vector<std::unique_ptr<Shape>> tempShapes;

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Cannot open the file.\n";
        return;
    }

    Clear();

    int widthF;
    int heightF;
    if (!(file >> widthF >> heightF))
    {
        std::cout << "Invalid file format.\n";
        return;
    }

    _width = widthF;
    _height = heightF;

    std::string type;

    while (file >> type)
    {
        std::unique_ptr<Shape> shape = nullptr;

        if (type == "circle")
        {
            shape = std::make_unique<Circle>(0, 0, 0, 0, "", false);
        }
        else if (type == "triangle")
        {
            shape = std::make_unique<Triangle>(0, 0, 0, 0, "", false);
        }
        else if (type == "rectangle")
        {
            shape = std::make_unique<Rectangle>(0, 0, 0, 0, 0, "", false);
        }
        else if (type == "line")
        {
            shape = std::make_unique<Line>(0, 0, 0, 0, false, "");
        }
        else
        {
            std::cout << "Invalid file format.\n";
            error = true;
            break;
        }

        if (shape != nullptr)
        {
            if (shape -> Deserialize(file))
            {
                tempShapes.push_back(std::move(shape));
            }
            else
            {
                std::cout << "Invalid format for " << type << ".\n";
                error = true;
                break;
            }
        }
    } 
    
    if (error)
    {
        return;
    }

    _shapes = std::move(tempShapes);

    if (_shapes.empty())
    {
        _selected = -1;
    }
    else
    {
        _selected = _shapes.size() - 1;
    }

    file.close();
    std::cout << "Board loaded.\n";
}

void Board::Clear()
{
    _shapes.clear();

    _selected = -1;

    std::cout << "Board was cleared.\n";
}

const std::vector<std::unique_ptr<Shape>>& Board::GetShapes() const
{
    return _shapes;
}

Shape* Board::GetSelected() const
{
    if (_selected == -1 || _selected >= _shapes.size())
    {
        return nullptr;
    }
    
    return _shapes[_selected].get();
}

int Board::GetWidth()
{
    return _width;
}

int Board::GetHeight()
{
    return _height;
}


Board::~Board()
{
    Clear();
}