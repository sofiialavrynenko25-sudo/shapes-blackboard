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
