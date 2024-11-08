#include "startinterface.h"
#include <windows.h>


void StartInterface::PrintFirst()//The process by which the snake appears from the left to the full appearance
{
    for (auto& point : startsnake)
    {
        point.Print();
        Sleep(speed);
    }
}

void StartInterface::PrintSecond()//The movement of a snake from left to right
{
    for (int i = 10; i != 40; ++i) //Snake head needs to move from 10 to 40
    {
        /*Calculate the next position of the snake's head and press it into startsnake, draw it, and remove the snake's tail*/
        int j = ( ((i-2)%8) < 4 )?( 15 + (i-2)%8 ) : ( 21 - (i-2)%8 );
        startsnake.emplace_back( Point(i, j) );
        startsnake.back().Print();
        startsnake.front().Clear();
        startsnake.pop_front();
        Sleep(speed);
    }
}

void StartInterface::PrintThird()//The process of the snake from touching the right side to disappearing
{
    while ( !startsnake.empty() || textsnake.back().GetX() < 33 ) //When the snake has not disappeared or the text has not moved to the specified position
    {
        if ( !startsnake.empty() ) //If the snake isn't gone, keep moving
        {
            startsnake.front().Clear();
            startsnake.pop_front();
        }
        ClearText();//Clear existing text
        PrintText();//Draws text after the updated position
        Sleep(speed);
    }
}

void StartInterface::PrintText()
{
    for (auto& point : textsnake)
    {
        if (point.GetX() >= 0)
            point.Print();
    }
}

void StartInterface::ClearText()
{
    for (auto& point : textsnake) //While clearing, move the text one space to the right
    {
        if (point.GetX() >= 0)
            point.Clear();
        point.ChangePosition(point.GetX() + 1, point.GetY());
    }
}

void StartInterface::Action()
{
    PrintFirst();
    PrintSecond();
    PrintThird();
}

