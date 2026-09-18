#include <iostream>
#include <fstream>
#include "board.h"
#include "shape.h"
#include "circle.h"
#include "triangle.h"
#include "line.h"
#include "rectangle.h"

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
            delete shape;
            return;
        }

        if (existShape -> IsEqual(shape))
        {
            std::cout << "Cannot add a shape with the same type and parameters.\n";
            delete shape;
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
        if (shape == nullptr)
        {
            continue;
        }

        std::string type = shape -> GetType();
        file << type << " " << shape -> GetId() << " " << shape -> GetX() << " " << shape -> GetY() << " ";

        if (type == "circle")
        {
            const Circle* circle = dynamic_cast<const Circle*>(shape);
            file << circle -> GetRadius() << " " << circle -> GetColor() << " " << circle -> GetIsFilled() << "\n";
        }
        else if (type == "triangle")
        {
            const Triangle* triangle = dynamic_cast<const Triangle*>(shape);
            file << triangle -> GetSide() << " " << triangle -> GetColor() << " " << triangle -> GetIsFilled() << "\n";
        }
        else if (type == "rectangle")
        {
            const Rectangle* rectangle = dynamic_cast<const Rectangle*>(shape);
            file << rectangle -> GetWidth() << " " << rectangle -> GetHeight() << " " << rectangle -> GetColor() << " " << rectangle -> GetIsFilled() << "\n";
        }
        else if (type == "line")
        {
            const Line* line = dynamic_cast<const Line*>(shape);
            file << line -> GetLength() << " " << line -> GetIsVertical() << " " << line -> GetColor() << "\n";
        }
    }

    file.close();
    std::cout << "Board saved.\n";
}

void Board::LoadFromFile(const std::string& filename)
{
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
        Shape* shape = nullptr;

        if (type == "circle")
        {
            int id, x, y, radius, fill;
            std::string color;

            file >> id >> x >> y >> radius >> color >> fill;

            shape = new Circle(id, x, y, radius, color, fill);
        }
        else if (type == "triangle")
        {
            int id, x, y, side, fill;
            std::string color;

            file >> id >> x >> y >> side >> color >> fill;

            shape = new Triangle(id, x, y, side, color, fill);
        }
        else if (type == "rectangle")
        {
            int id, x, y, width, height, fill;
            std::string color;

            file >> id >> x >> y >> width >> height >> color >> fill;

            shape = new Rectangle(id, x, y, width, height, color, fill);
        }
        else if (type == "line")
        {
            int id, x, y, length, isVertical;
            std::string color;

            file >> id >> x >> y >> length >> isVertical >> color;

            shape = new Line(id, x, y, length, isVertical, color);
        }

        if (shape != nullptr)
        {
            _shapes.push_back(shape);
        }
    }   

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

Shape* Board::GetSelected()
{
    if (_selected == -1 || _selected >= _shapes.size())
    {
        return nullptr;
    }
    
    return _shapes[_selected];
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