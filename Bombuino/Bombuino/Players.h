

#ifndef _Players_h
#define _Players_h
#pragma once
#include <Gamebuino-Meta.h>
#include "Utils.h"
#include "General.h"
#include "Entity.h"





#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum positionMove
{
    UP = -8,
    DOWN = 8,
    LEFT = -7,
    RIGHT = 7,
};


class Players : Entity {
public:
    static const int WIDTH = 5;
    static const int HEIGHT = 6;
    static const int PlayersMaxBombe = 2;


    int BombePosingNumber = 0;
    Players* PlayersCible = nullptr;
    int IndexPlayers;
    Color colorPlayers;
    Image img;

    int TimerToMove = Utils::RandomTimePnjAction();

    Players(int x, int y, TypeEntity typeEntity, int indexPlayers, Image image, const Color colorIA = WHITE) {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        IndexPlayers = indexPlayers;
        _typeEntity = typeEntity;
        img = image;
        if (typeEntity == TypeEntity::Ia)
        {
            colorPlayers = colorIA;
        }
    }

    int getX() {
        return _x;
    }
    int getY() {
        return _y;
    }
    int getWidth() {
        return _width;
    }
    int getHeight() {
        return _height;
    }
    TypeEntity getType() {
        return getTypeEntity();
    }

    void Move(positionMove move) {
        switch (move)
        {
        case positionMove::DOWN:
            if (PlayersCanMove(DOWN)) {
                _y += DOWN;
            }
            break;
        case positionMove::LEFT:
            if (PlayersCanMove(LEFT)) {
                _x += LEFT;
            }
            break;
        case positionMove::RIGHT:
            if (PlayersCanMove(RIGHT)) {
                _x += RIGHT;
            }
            break;
        case positionMove::UP:
            if (PlayersCanMove(UP)) {
                _y += UP;
            }
            break;
        }
    }

    void getCible(Players* PlayersArray[])
    {
        int cibleInt = IndexPlayers;
        while (cibleInt == IndexPlayers)
        {
            cibleInt = rand() % 3;
        }
        PlayersCible = PlayersArray[cibleInt];
    }

    void update() {
        if (getTypeEntity() == TypeEntity::Ia)
        {
            gb.display.setColor(colorPlayers);
            gb.display.fillCircle(_x, _y, 2);
            DebugPnj();
            TimerToMove--;
            DeplacementPnj(this);
        }
        else
        {
            gb.display.drawImage(_x, _y, img);
        }

    }
    /// <summary>
    /// Affiche un cercle sur la cible du joueur qui le prends en chasse
    /// </summary>
    void DebugPnj() {
        gb.display.drawCircle(PlayersCible->getX(), PlayersCible->getY(), 5);
        gb.display.print(IndexPlayers);
        gb.display.print(".");
        gb.display.print(PlayersCible->IndexPlayers);
        gb.display.print("-");
    }

    bool PlayersCanMove(positionMove moveTO) {
        bool tmp = true;

        if (moveTO == positionMove::LEFT || moveTO == positionMove::RIGHT)
        {
            // si on sort de l'écran
            if (this->getX() + moveTO <= 0 || this->getX() + moveTO >= 77) {
                return false;
            }
            gb.display.setCursor(0, 0);
            gb.display.setColor(YELLOW);

            // si la position du joueur + ou - X entre en collision avec une entity alors il ne bouge pas
            for (Entity* entity : General::EntityArray) {

                if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), this->getX() + moveTO, this->getY(), this->getWidth(), this->getHeight())) {
                    tmp = false;
                }
            }

        }
        else {

            if (this->getY() + moveTO < 7 || this->getY() + moveTO >= 63) {
                return false;
            }

            // si la position du joueur + ou - Y entre en collision avec une entity alors il ne bouge pas
            for (Entity* entity : General::EntityArray) {
                if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), this->getX(), this->getY() + moveTO, this->getWidth(), this->getHeight())) {
                    tmp = false;
                }
            }
        }

        return tmp;
    }

    void DeplacementPnj(Players* player) {
        if (TimerToMove > 0) {
            return;
        }

        TimerToMove = Utils::RandomTimePnjAction();
        /*======================== GESTION DEPLACEMENT HAUT BAS =======================*/
            //  pnj va en haut sinon il va en bas
        if (this->PlayersCible->getY() < _y) {
            TypeEntity typeEntite = GetTypeEntityAround(UP);

            if (typeEntite == TypeEntity::briquesDestructible) {
                //Bombe::PoseBombe(this);


            }

            Move(positionMove::UP);
        }
        else {
            Move(positionMove::DOWN);
        }

        // si pas d'obstacle avance 
        // si rencontre un bloc pose une bombe. 


    /*======================== GESTION DEPLACEMENT COTÉ =======================*/
    // si le x du joueur cible est plus petit que moi 
    // je vais a gauche sinon a droite

        // si pas d'obstacle avance 
        // si rencontre un bloc pose une bombe. 
        if (this->PlayersCible->getX() < _x) {
            Move(positionMove::LEFT);
        }
        else {
            Move(positionMove::RIGHT);
        }
    }

    TypeEntity GetTypeEntityAround(positionMove moveTO)
    {
        TypeEntity tmp = TypeEntity::none;
        if (moveTO == positionMove::LEFT || moveTO == positionMove::RIGHT)
        {
            // si on sort de l'écran
            if (this->getX() + moveTO <= 0 || this->getX() + moveTO >= 77) {
                return TypeEntity::none;
            }
            gb.display.setCursor(0, 0);
            gb.display.setColor(YELLOW);

            // si la position du joueur + ou - X entre en collision avec une entity alors il ne bouge pas
            for (Entity* entity : General::EntityArray) {

                if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), entity->getX() + moveTO, entity->getY(), entity->getWidth(), entity->getHeight())) {
                    tmp = entity->getTypeEntity();
                }
            }

        }
        else {

            if (this->getY() + moveTO < 7 || this->getY() + moveTO >= 63) {
                tmp = TypeEntity::none;
            }

            // si la position du joueur + ou - Y entre en collision avec une entity alors il ne bouge pas
            for (Entity* entity : General::EntityArray) {
                if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), entity->getX(), entity->getY() + moveTO, entity->getWidth(), entity->getHeight())) {
                    tmp = entity->getTypeEntity();
                }
            }
        }

        return tmp;
    }

};


#endif

