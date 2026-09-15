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