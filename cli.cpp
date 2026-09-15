#include <iostream>
#include <vector> 
#include <cmath>
#include <string>

#include "shape.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "line.h"
#include "cli.h"

void CLI::Draw()
{
    std::cout << "Drawing the board...\n";
    _board.Draw();
}

void CLI::List()
{
    std::vector<Shape*> shapes = _board.GetShapes();

    if (shapes.empty())
    {
        std::cout << "There are no shapes added, cannot list them.\n";
        return;
    }

    std::cout << "All added shapes listed:\n";

    for (const auto& shape : shapes)
    {
        std::cout << shape -> ToString() + "\n";
    }
}

void CLI::Shapes()
{
    std::cout << "All possible shapes (with parameters):\n";

    std::cout << "1. circle [id, x, y, radius, color, isFilled]\n";
    std::cout << "2. triangle [id, x, y, side, color, isFilled]\n";
    std::cout << "3. rectangle [id, x, y, width, height, color, isFilled]\n";
    std::cout << "4. line [id, x, y, length, color]\n";
}

void CLI::Add() 
{
    int inputType = -1;

    std::cout << "What shape do you want to add?\n";
    std::cout << "1. circle\n";
    std::cout << "2. triangle\n";
    std::cout << "3. rectangle\n";
    std::cout << "4. line\n\n";

    std::cout << "Please, choose your option:\n";
    if (!(std::cin >> inputType))
    {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }
    
    int inputId = -1;

    std::cout << "Please, enter an ID:\n";
    if (!(std::cin >> inputId))
    {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    int inputX = -1;

    std::cout << "Please, enter an X coordinate:\n";
    if (!(std::cin >> inputX))
    {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    int inputY = -1;

    std::cout << "Please, enter an Y coordinate:\n";
    if (!(std::cin >> inputY))
    {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    std::string inputColor = "";

    std::cout << "Please, enter a color:\n";
    std::cin >> inputColor;

    switch (inputType)
    {
        case 1:
        {
            int radius;
            int fill;

            std::cout << "Please, enter a radius:\n";
            if (!(std::cin >> radius))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            std::cout << "Please, enter a filling option (1 - filled, 0 - outlined):\n";
            if (!(std::cin >> fill))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            _board.AddShape(new Circle(inputId, inputX, inputY, radius, inputColor, fill != 0));

            break;
        }
        case 2:
        {
            int side;
            int fill;

            std::cout << "Please, enter a side:\n";
            if (!(std::cin >> side))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            std::cout << "Please, enter a filling option (1 - filled, 0 - outlined):\n";
            if (!(std::cin >> fill))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            _board.AddShape(new Triangle(inputId, inputX, inputY, side, inputColor, fill != 0));

            break;
        }
        case 3:
        {
            int width;
            int height;
            int fill;

            std::cout << "Please, enter a width:\n";
            if (!(std::cin >> width))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            std::cout << "Please, enter a height:\n";
            if (!(std::cin >> height))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            std::cout << "Please, enter a filling option (1 - filled, 0 - outlined):\n";
            if (!(std::cin >> fill))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            _board.AddShape(new Rectangle(inputId, inputX, inputY, width, height, inputColor, fill != 0));

            break;
        }
        case 4:
        {
            int length;
            int vertical;

            std::cout << "Please, enter a length:\n";
            if (!(std::cin >> length))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            std::cout << "Please, enter a position option (1 - vertical, 0 - horizontal):\n";
            if (!(std::cin >> vertical))
            {
                std::cout << "Invalid input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }

            _board.AddShape(new Line(inputId, inputX, inputY, length, vertical != 0, inputColor));

            break;
        }
        default:
        {
            std::cout << "Invalid type.\n";
            break;
        }
    }
}

void CLI::Select()
{
    int id;

    std::cout << "Please, enter an ID to select a shape:\n";
    if (!(std::cin >> id))
    {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    _board.SelectShape(id);
}

void CLI::Remove()
{
    _board.RemoveSelected();
}

void CLI::Move()
{
    int newX;
    int newY;

    std::cout << "Please, enter a new X coordinate:\n";
    if (!(std::cin >> newX))
    {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    std::cout << "Please, enter a new Y coordinate:\n";
    if (!(std::cin >> newY))
    {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    _board.MoveSelected(newX, newY);
}

void CLI::Clear()
{
    _board.Clear();
}

void CLI::Run()
{
    int input = -1;

    while (input != 11)
    {
        std::cout << "\nMENU\n";
        std::cout << "1 - Draw\n";
        std::cout << "2 - List\n";
        std::cout << "3 - Shapes\n";
        std::cout << "4 - Add\n";
        std::cout << "5 - Select\n";
        std::cout << "6 - Remove\n";
        std::cout << "7 - Edit\n";
        std::cout << "8 - Paint\n";
        std::cout << "9 - Move\n";
        std::cout << "10 - Clear\n";
        std::cout << "11 - Exit\n\n";

        std::cout << "Please, enter your option:\n";
        if (!(std::cin >> input))
        {
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (input)
        {
            case 1: 
            {
                Draw();
                break;
            }
            case 2:
            {
                List();
                break;
            }
            case 3:
            {
                Shapes();
                break;
            }
            case 4:
            {
                std::cout << "No implementation yet.\n";
                break;
            }
            case 5:
            {
                std::cout << "No implementation yet.\n";
                break;
            }
            case 6:
            {
                std::cout << "No implementation yet.\n";
                break;
            }
            case 7:
            {
                std::cout << "No implementation yet.\n";
                break;
            }
            case 8:
            {
                std::cout << "No implementation yet.\n";
                break;
            }
            case 9:
            {
                std::cout << "No implementation yet.\n";
                break;
            }
            case 10:
            {
                std::cout << "No implementation yet.\n";
                break;
            }
            case 11:
            {
                std::cout << "Exiting the program...\n";
                break;
            }
            default:
            {
                std::cout << "Invalid option.\n";
                break;
            }
        }
    }
}