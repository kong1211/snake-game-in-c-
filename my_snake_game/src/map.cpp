#include "map.h"
#include <windows.h>

void Map::PrintInitmap()//Initial mapping
{
    for (auto& point : initmap)
    {
        point.Print();
        Sleep(10);//use the Sleep function to create an animation effect
    }
}
