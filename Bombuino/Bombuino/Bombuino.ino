/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "Entity.h"
#include "Utils.h"
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

enum positionMove
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

class Player : Entity {
    public :
        Player(int x, int y, int width, int height) {
            _x = x;
            _y = y;
            _width = width;
            _height = height;
            gb.display.fillRect(_x, _y, _width, _height);
        }

        void update(Button move) {
            switch (move)
            {
            case Gamebuino_Meta::Button::down:
                _y += 8;
                break;
            case Gamebuino_Meta::Button::left:
                _x -= 8;
                break;
            case Gamebuino_Meta::Button::right:
                _x += 8;
                break;
            case Gamebuino_Meta::Button::up:
                _y -= 8;
                break;
            case Gamebuino_Meta::Button::a:
                break;
            case Gamebuino_Meta::Button::b:
                break;
            case Gamebuino_Meta::Button::menu:
                break;
            case Gamebuino_Meta::Button::home:
                break;
            default:
                break;
            }
        } 

        void update() {
            gb.display.fillRect(_x, _y, _width, _height);
        }

};


Brique* briqueArray[99];
Player* p;
void setup() {
	gb.begin();
    CreateBriqueIndestructible();
    p = new Player(2, 18, 5, 5);
}


void loop() {
    while (!gb.update());
    gb.display.clear();
    TouchEvent();
    p->update();
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

void TouchEvent() {

    if (gb.buttons.pressed(BUTTON_UP)) {
        p->update(BUTTON_UP);
    }
    if (gb.buttons.pressed(BUTTON_DOWN)) {
        p->update(BUTTON_DOWN);
    }
    if (gb.buttons.pressed(BUTTON_LEFT)) {
        p->update(BUTTON_LEFT);
    }
    if (gb.buttons.pressed(BUTTON_RIGHT)) {
        p->update(BUTTON_RIGHT);
    }
}