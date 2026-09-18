#include <iostream>
#include <vector> 
#include <cmath>
#include <string>
#include <sstream>

#include "shape.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "line.h"
#include "cli.h"

void CLI::Process(const std::string& input)
{
    if (input.empty())
    {
        return;
    }

    std::stringstream ss(input);
    std::string command;
    ss >> command;

    int boardW = _board.GetWidth();
    int boardH = _board.GetHeight();

    if (command == "draw")
    {
        _board.Draw();
    }
    else if (command == "list")
    {
        std::vector<Shape*> shapes = _board.GetShapes();

        if (shapes.empty())
        {
            std::cout << "There are no shapes added, cannot list them.\n";
            return;
        }
        
        std::cout << "All shapes added: \n\n";

        for (const auto& shape : shapes)
        {
            std::cout << shape -> ToString() << "\n";
        };
    }
    else if (command == "shapes")
    {
        std::cout << "All available shapes:\n\n";
        std::cout << "circle [id] [x] [y] [radius] [color] [fill option]\n";
        std::cout << "triangle [id] [x] [y] [side] [color] [fill option]\n";
        std::cout << "rectangle [id] [x] [y] [width] [height] [color] [fill option]\n";
        std::cout << "line [id] [x] [y] [length] [position option] [color]\n";
    }
    else if (command == "add")
    {
        std::string type;

        if (!(ss >> type))
        {
            std::cout << "Invalid shape type.\n";
            return;
        }

        Shape* newShape = nullptr;

        if (type == "circle")
        {
            int id, x, y, radius, fill;
            std::string color;
            
            if (!(ss >> id >> x >> y >> radius >> color >> fill))
            {
                std::cout << "Invalid arguments for circle.\n";
                return;
            }

            if (radius * 2 >= boardH || radius * 2 >= boardW)
            {
                std::cout << "Shape cannot be bigger than a board.\n";
                return;
            }

            newShape = new Circle(id, x, y, radius, color, fill != 0);
        }
        else if (type == "triangle")
        {
            int id, x, y, side, fill;
            std::string color;
            
            if (!(ss >> id >> x >> y >> side >> color >> fill))
            {
                std::cout << "Invalid arguments for triangle.\n";
                return;
            }
            
            float triangleH = (side * std::sqrt(3)) / 2.0;

            if (triangleH >= boardH || side >= boardW)
            {
                std::cout << "Shape cannot be bigger than a board.\n";
                return;
            }

            newShape = new Triangle(id, x, y, side, color, fill != 0);
        }
        else if (type == "rectangle")
        {
            int id, x, y, width, height, fill;
            std::string color;
            
            if (!(ss >> id >> x >> y >> width >> height >> color >> fill))
            {
                std::cout << "Invalid arguments for rectangle.\n";
                return;
            }

            if (width >= boardW || height >= boardH)
            {
                std::cout << "Shape cannot be bigger than a board.\n";
                return;
            }

            newShape = new Rectangle(id, x, y, width, height, color, fill != 0);
        }
        else if (type == "line")
        {
            int id, x, y, length, isVert;
            std::string color;
            
            if (!(ss >> id >> x >> y >> length >> isVert >> color))
            {
                std::cout << "Invalid arguments for line.\n";
                return;
            }

            if ((isVert && length >= boardH) || (!isVert && length >= boardW))
            {
                std::cout << "Shape cannot be bigger than a board.\n";
                return;
            }

            newShape = new Line(id, x, y, length, isVert != 0, color);
        }
        else
        {
            std::cout << "Unknown shape type.\n";
            return;
        }

        if (newShape != nullptr)
        {
            _board.AddShape(newShape);
        }
    }
    else if (command == "select")
    {
        int parameterFirst;

        if (!(ss >> parameterFirst))
        {
            std::cout << "Invalid select arguments.\n";
            return;
        }

        int parameterSecond;
        if (ss >> parameterSecond)
        {
            int x = parameterFirst;
            int y = parameterSecond;
            
            _board.SelectShapeCoord(x, y);
        }
        else
        {
            int id = parameterFirst;

            _board.SelectShape(id);
        }
    }
    else if (command == "remove")
    {
        _board.RemoveSelected();
    }
    else if (command == "edit")
    {
        Shape* selected = _board.GetSelected();

        if (selected == nullptr)
        {
            std::cout << "No shape selected.\n";
            return;
        }

        if (selected -> EditParameters(ss, _board.GetWidth(), _board.GetHeight()))
        {
            std::cout << selected -> GetId() << " " << selected -> GetType() << " parameters updated.\n";
        }
        else
        {
            std::cout << "Invalid editing parameters.\n";
        }
    }
    else if (command == "paint")
    {
        std::string color;

        if (!(ss >> color))
        {
            std::cout << "Invalid color argument.\n";
            return;
        }

        Shape* selected = _board.GetSelected();

        if (selected == nullptr)
        {
            std::cout << "No shape selected.\n";
            return;
        }

        selected ->SetColor(color);

        std::cout << selected -> GetId() << " " << selected -> GetType() << " was painted.\n";
    }
    else if (command == "move")
    {
        int newX, newY;

        if (!(ss >> newX >> newY))
        {
            std::cout << "Invalid new coordinates arguments.\n";
            return;
        }

        _board.MoveSelected(newX, newY);
    }
    else if (command == "clear")
    {
        _board.Clear();
    }
    else if (command == "save")
    {
        std::string filename;

        if (!(ss >> filename))
        {
            std::cout << "Invalid save arguments.\n";
            return;
        }

        _board.SaveToFile(filename);
    }
    else if (command == "load")
    {
        std::string filename;

        if (!(ss >> filename))
        {
            std::cout << "Invalid load arguments.\n";
            return;
        }

        _board.LoadFromFile(filename);
    }
    else
    {
        std::cout << "Unknown command.\n";
    }
}
