#include "point.h"
#include "tools.h"
#include <iostream>

void Point::Print()//Output box
{
    SetCursorPosition(x, y);
    std::cout << "-" ;
}

void Point::PrintCircular()//Output circle
{
    SetCursorPosition(x, y);
    std::cout << "." ;
}

void Point::Clear()//Clear output
{
    SetCursorPosition(x, y);
    std::cout << "  " ;
}

void Point::ChangePosition(const int x, const int y)//Change coordinates
{
    this->x = x;
    this->y = y;
}
