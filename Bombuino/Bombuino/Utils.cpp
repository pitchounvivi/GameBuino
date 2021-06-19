// 
// 
// 

#include "Utils.h"
#include <Gamebuino-Meta.h>

void Utils::DebugMessageOnTopScreen(String texte, int value)
{
    gb.display.setCursorY(2);
    gb.display.setCursorX(2);
    gb.display.print(texte + ":");
    gb.display.print(value);
}

void Utils::DebugMessageOnBottomScreen(String texte, int value)
{
    gb.display.setColor(WHITE);
    gb.display.setCursorY(50);
    gb.display.setCursorX(2);
    gb.display.print(texte + ":");
    gb.display.print(value);
}
