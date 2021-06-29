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


class Bombe : public Entity {

public:

    int TimerBombe = General::BOMBE_TIMER;
    Color color = gb.createColor(255, TimerBombe, 38);
    static const int WIDTH = 5;
    static const int HEIGHT = 6;
    Image explo_texture = Image(Utils::EXPLOSION_TEXTURE);
    Image bombe_texture = Image(Utils::BOMB_TEXTURE);

    Bombe(int x, int y) {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        _typeEntity = TypeEntity::bombes;
    };

    void update() {
        if (TimerBombe <= 14) {
            gb.display.drawImage(_x - Brique::WIDTH - 1, _y - Brique::HEIGHT - 1, explo_texture);
        } else {
            gb.display.drawImage(_x, _y, bombe_texture);
        }
        if (TimerBombe <= 0) {
            checkBombeAlentour();
            General::entities.remove(this);
            return;
        }
        color = gb.createColor(255, TimerBombe, 38);
        TimerBombe -= 1;
    }
    int GetTimerBombe() {
        return TimerBombe;
    }

    void checkBombeAlentour()
    {
        const Node<Entity>* iteratorEntity = General::entities.get_head();

        while (iteratorEntity)
        {
            Entity* ent = iteratorEntity->_current;

            // Je suis une brique ou un Players si oui je check les coord haut bas gauche droite et je delete l'entity
            if (ent->getTypeEntity() == TypeEntity::briquesDestructible &&
                (gb.collide.rectRect(_x + MOVES::RIGHT, _y, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()) ||
                 gb.collide.rectRect(_x + MOVES::LEFT, _y, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()) ||
                 gb.collide.rectRect(_x, _y + MOVES::UP, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()) ||
                 gb.collide.rectRect(_x, _y + MOVES::DOWN, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()))) {
                // si c'est une brique
                iteratorEntity = iteratorEntity->_next;
                General::entities.remove(ent);
                continue;
            }
            iteratorEntity = iteratorEntity->_next;
        }

        const Node<Entity>* iterator = (Node<Entity> *)General::players.get_head();


        while (iterator) {
            Entity* player = iterator->_current;

            if (gb.collide.rectRect(_x, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()) ||
                gb.collide.rectRect(_x + MOVES::RIGHT, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()) ||
                gb.collide.rectRect(_x + MOVES::LEFT, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()) ||
                gb.collide.rectRect(_x, _y + MOVES::UP, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()) ||
                gb.collide.rectRect(_x, _y + MOVES::DOWN, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight())) {
                // si c'est une brique
                iterator = iterator->_next;
                General::players.remove((Players *)player);
                continue;
            }
            iterator = iterator->_next;
        }
    }
};


#endif

