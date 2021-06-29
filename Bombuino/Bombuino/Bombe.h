// Bombe.h

#ifndef _BOMBE_h
#define _BOMBE_h
#pragma once
#include <Gamebuino-Meta.h>
#include "Utils.h"
#include "Entity.h"
#include "General.h"
#include "Brique.h"
#include "MOVES.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Players;

class Bombe : public Entity {

public:

    int TimerBombe = General::BOMBE_TIMER;
    Color color = gb.createColor(255, TimerBombe, 38);
    static const int WIDTH = 5;
    static const int HEIGHT = 6;
    Image explo_texture = Image(Utils::EXPLOSION_TEXTURE);
    Image bombe_texture = Image(Utils::BOMB_TEXTURE);
    Players* _playerRef = nullptr;

    Bombe(int x, int y, Players* playerRef);

    void update();

    int getTimerBombe();

    void checkBombeAlentour();
};


#endif

