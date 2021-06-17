/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "Entity.h"
#include <Gamebuino-Meta.h>
#include <cstdlib>


class Brique : public Entity {
public:
    bool _isBreakeable;
    Brique(int x , int y, int width,int height, bool breakeable) {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
        _isBreakeable = breakeable;
    }

    void update() {

    }
};

Brique* briqueArray[99];

void setup() {
	gb.begin();
    CreateBriqueIndestructible();
}


void loop() {
    while (!gb.update());
    gb.display.clear();
    DebugTopScreen("Informations ", 00);
    gb.display.drawFastHLine(0, 8, gb.display.width());
    DrawBrique();
}


void CreateBriqueDestructible() {

}

void CreateBriqueIndestructible() {
    int EcartBriqueX = 14;
    int EcartBriqueY = 16;
    int cpt = 0;

    for (int y = 17; y < 63; y += EcartBriqueY) {
        for (int x = 8; x < 77; x += EcartBriqueX) {
            briqueArray[cpt++] = new Brique(x, y, 7, 8, false);
        }
    }
}



void DrawBrique() {
    for (Brique *brique : briqueArray) {
        if (brique->_isBreakeable == false) {
            gb.display.setColor(BROWN);
            gb.display.fillRect(brique->getX(), brique->getY(), brique->getWidth(), brique->getHeight());
            gb.display.setColor(WHITE);
        }
    }
}


void DebugTopScreen(String texte, int value) {
    gb.display.setCursorY(2);
    gb.display.setCursorX(2);
    gb.display.print(texte + ":");
    gb.display.print(value);
}

void DebugBottomScreen(String texte, int value)
{
    gb.display.setColor(WHITE);
    gb.display.setCursorY(50);
    gb.display.setCursorX(2);
    gb.display.print(texte + ":");
    gb.display.print(value);
}
