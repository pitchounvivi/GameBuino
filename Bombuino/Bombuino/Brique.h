// Brique.h

#ifndef _BRIQUE_h
#define _BRIQUE_h
#include <Gamebuino-Meta.h>
#include "Entity.h"
#include "Utils.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Brique : public Entity {
public:

    static const int WIDTH = 7;
    static const int HEIGHT = 8;

    Brique(int x, int y, bool isbreakble = false)
    {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        if (isbreakble) {
            _typeEntity = TypeEntity::BRIQUES_BREAK;
        }
        else {
            _typeEntity = TypeEntity::BRIQUES;
        }

    }

    void update() {
        if (getTypeEntity() == TypeEntity::BRIQUES_BREAK) {
            gb.display.drawImage(_x, _y, Utils::BRIQUE_DESTRUCTIBLE);
        }
        else {
            gb.display.drawImage(_x, _y, Utils::BRIQUE_INCASSABLE);
        }
    };
};

#endif

