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
        std::cout << "line [id] [x] [y] [length] [position option] [color] [fill option]\n";
    }
    else if (command == "add")
    {
        std::string type;

        if (!(ss >> type))
        {
            std::cout << "Invalid shape type.\n";
            return;
        }

        if (type == "circle")
        {
            int id, x, y, radius, fill;
            std::string color;
            
            if (!(ss >> id >> x >> y >> radius >> color >> fill))
            {
                std::cout << "Invalid arguments for circle.\n";
                return;
            }

            _board.AddShape(new Circle(id, x, y, radius, color, fill != 0));
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

            _board.AddShape(new Triangle(id, x, y, side, color, fill != 0));
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

            _board.AddShape(new Rectangle(id, x, y, width, height, color, fill != 0));
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

            _board.AddShape(new Line(id, x, y, length, isVert != 0, color));
        }
        else
        {
            std::cout << "Unknown shape type.\n";
        }
    }
    else if (command == "select")
    {
        int id;

        if (!(ss >> id))
        {
            std::cout << "No ID for selection.\n";
            return;
        }

        _board.SelectShape(id);
    }
    else if (command == "remove")
    {
        _board.RemoveSelected();
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
}