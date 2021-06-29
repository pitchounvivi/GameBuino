// Bombe.h

#ifndef _BOMBE_h
#define _BOMBE_h
#pragma once
#include <Gamebuino-Meta.h>
#include "Utils.h"
#include "Entity.h"
#include "General.h"
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
    static const int WIDTH = 5;
    static const int HEIGHT = 6;
    Image Explosion = Image(Utils::EXPLOSION_TEXTURE);
    Image BombeImg = Image(Utils::BOMB_TEXTURE);

    Bombe(int x, int y, int indexBombe) {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        _indexBombe = indexBombe;
        _typeEntity = TypeEntity::bombes;
    };

    void update() {
        if (TimerBombe <= 14) {
            gb.display.drawImage(_x - Brique::WIDTH - 1, _y - Brique::HEIGHT - 1, Explosion);
        }
        else {
            gb.display.drawImage(_x, _y, BombeImg);
        }


        if (TimerBombe <= 0) {
            General::EntityArray[_indexBombe] = nullptr;
            checkBombeAlentour();
            return;
        }
        colorBombe = gb.createColor(255, TimerBombe, 38);
        TimerBombe -= 1;
    }
    int GetTimerBombe() {
        return TimerBombe;
    }

    void checkBombeAlentour()
    {

        for (int i = 0;i < General::maxEntite; i++)
        {
            if (General::EntityArray[i] == nullptr)
            {
                continue;
            }
            Entity* ent = General::EntityArray[i];

            // Je suis une brique ou un Players ?
            if (ent->getTypeEntity() == TypeEntity::briquesDestructible)
            {

                // Collision avec le carré  de droite ?
                if (gb.collide.rectRect(_x + General::RightMove, _y, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()))
                {

                    // si c'est une brique
                    General::EntityArray[i] = nullptr;
                }
                // Collision avec le carré de gauche? 
                if (gb.collide.rectRect(_x + General::LeftMove, _y, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()))
                {
                    General::EntityArray[i] = nullptr;
                }
                // Collision avec le carré d'en haut?
                if (gb.collide.rectRect(_x, _y + General::UpMove, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()))
                {
                    General::EntityArray[i] = nullptr;
                }
                // si collision avec le carré du bas 
                if (gb.collide.rectRect(_x, _y + General::DownMove, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()))
                {
                    General::EntityArray[i] = nullptr;
                }
            }
        }


        for (int i = 0; i < General::NbPlayer;i++) 
        {
            if (General::PlayersArrays[i] == nullptr)
            {
                continue;
            }
            Entity* player = General::PlayersArrays[i];

            if (gb.collide.rectRect(_x, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()))
            {
                // on le met personnage a 0
                General::PlayersArrays[i] = nullptr;

                // si l'entity est un player
                if (player->getTypeEntity() == TypeEntity::players)
                {
                    General::generalTexte = "GAME OVER";
                }

                // si l'entity est un pnj
                if (player->getTypeEntity() == TypeEntity::Ia)
                {
                    General::generalTexte = "YOU WIN";
                }
            }

            // Collision avec le carré  de droite ?
            if (gb.collide.rectRect(_x + General::RightMove, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()))
            {
                // on le met personnage a 0
                General::PlayersArrays[i] = nullptr;

                // si l'entity est un player
                if (player->getTypeEntity() == TypeEntity::players)
                {
                    General::generalTexte = "GAME OVER";
                }

                // si l'entity est un pnj
                if (player->getTypeEntity() == TypeEntity::Ia)
                {
                    General::generalTexte = "YOU WIN";
                }
            }
            // Collision avec le carré de gauche? 
            if (gb.collide.rectRect(_x + General::LeftMove, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()))
            {
                // on le met personnage a 0
                General::PlayersArrays[i] = nullptr;

                // si l'entity est un player
                if (player->getTypeEntity() == TypeEntity::players)
                {
                    General::generalTexte = "GAME OVER";
                }

                // si l'entity est un pnj
                if (player->getTypeEntity() == TypeEntity::Ia)
                {
                    General::generalTexte = "YOU WIN";
                }
            }
            // Collision avec le carré d'en haut?
            if (gb.collide.rectRect(_x, _y + General::UpMove, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()))
            {
                // on le met personnage a 0
                General::PlayersArrays[i] = nullptr;

                // si l'entity est un player
                if (player->getTypeEntity() == TypeEntity::players)
                {
                    General::generalTexte = "GAME OVER";
                }

                // si l'entity est un pnj
                if (player->getTypeEntity() == TypeEntity::Ia)
                {
                    General::generalTexte = "YOU WIN";
                }
            }
            // si collision avec le carré du bas 
            if (gb.collide.rectRect(_x, _y + General::DownMove, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()))
            {
                // on le met personnage a 0
                General::PlayersArrays[i] = nullptr;
                
                // si l'entity est un player
                if (player->getTypeEntity() == TypeEntity::players)
                {
                    General::generalTexte = "GAME OVER";
                }

                // si l'entity est un pnj
                if (player->getTypeEntity() == TypeEntity::Ia)
                {
                    General::generalTexte = "YOU WIN";
                }
            }
        }
    }
};


#endif

