// Bombe.h

#ifndef _BOMBE_h
#define _BOMBE_h
#pragma once
#include <Gamebuino-Meta.h>
#include "Utils.h"
#include "Entity.h"
#include "General.h"
#include "Players.h"
#include "Brique.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class Bombe : public Entity {

public:

    int TimerBombe = General::BombeTimer;
    Color colorBombe = gb.createColor(255, TimerBombe, 38);
    int _indexBombe;
    Players* _PlayerPosingBomb;
    static const int WIDTH = 5;
    static const int HEIGHT = 6;
    Image Explosion = Image(Utils::EXPLOSION_TEXTURE);
    Image BombeImg = Image(Utils::BOMB_TEXTURE);

    Bombe(int x, int y, int indexBombe, Players* PlayerPoseBombe) {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        _indexBombe = indexBombe;
        _PlayerPosingBomb = PlayerPoseBombe;
        _typeEntity = TypeEntity::bombes;
    };

    int testctp = 0;
    void update() {
        if (TimerBombe <= 14) {
            gb.display.drawImage(_x - Brique::WIDTH - 1, _y - Brique::HEIGHT - 1, Explosion);
        }
        else {
            gb.display.drawImage(_x, _y, BombeImg);
        }


        if (TimerBombe <= 0) {
            General::EntityArray[_indexBombe] = nullptr;
            _PlayerPosingBomb->BombePosingNumber--;

            if (_PlayerPosingBomb->BombePosingNumber <= 0) {
                _PlayerPosingBomb->BombePosingNumber = 0;
            }
            checkBombeAlentour();
            return;
        }
        colorBombe = gb.createColor(255, TimerBombe, 38);
        TimerBombe -= 1;
    }

    void checkBombeAlentour()
    {

        for (int i = 0;i < General::maxEntite; i++)
        {
            if (General::EntityArray[i] == nullptr)
            {
                continue;
            }
            Entity* tmp = General::EntityArray[i];

            // Je suis une brique ou un Players ?
            if (tmp->getTypeEntity() == TypeEntity::briquesDestructible || tmp->getTypeEntity() == TypeEntity::players)
            {

                // Collision avec le carré  de droite ?
                if (gb.collide.rectRect(_x + positionMove::RIGHT, _y, Bombe::WIDTH, Bombe::HEIGHT, tmp->getX(), tmp->getY(), tmp->getWidth(), tmp->getHeight()))
                {
                    // si c'est mon joueur 

                    // si c'est une brique ou une IA:
                    General::EntityArray[i] = nullptr;
                }
                // Collision avec le carré de gauche? 
                if (gb.collide.rectRect(_x + positionMove::LEFT, _y, Bombe::WIDTH, Bombe::HEIGHT, tmp->getX(), tmp->getY(), tmp->getWidth(), tmp->getHeight()))
                {
                    General::EntityArray[i] = nullptr;
                }
                // Collision avec le carré d'en haut?
                if (gb.collide.rectRect(_x, _y + positionMove::UP, Bombe::WIDTH, Bombe::HEIGHT, tmp->getX(), tmp->getY(), tmp->getWidth(), tmp->getHeight()))
                {
                    General::EntityArray[i] = nullptr;
                }
                // si collision avec le carré du bas 
                if (gb.collide.rectRect(_x, _y + positionMove::DOWN, Bombe::WIDTH, Bombe::HEIGHT, tmp->getX(), tmp->getY(), tmp->getWidth(), tmp->getHeight()))
                {
                    General::EntityArray[i] = nullptr;
                }
            }


        }
    }


    static void PoseBombe(Players* player) {
        if (player->BombePosingNumber == Players::PlayersMaxBombe) {
            return;
        }
    
        General::EntityArray[General::CompteurEntite] = new Bombe(player->getX(), player->getY(), General::CompteurEntite, player);
    
        General::CompteurEntite++;
    
        if (General::CompteurEntite >= General::maxEntite)
        {
            General::CompteurEntite = 0;
        }
        player->BombePosingNumber++;
    }
};


#endif

