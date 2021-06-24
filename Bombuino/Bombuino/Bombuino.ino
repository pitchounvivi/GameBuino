/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "General.h"
#include "Entity.h"
#include "Players.h"
#include "Utils.h"
#include <Gamebuino-Meta.h>
#include <cstdlib>


Image PlayersImg(Utils::ROBOT_TEXTURE);
Image Explosion(Utils::EXPLOSION_TEXTURE);
Image BombeImg(Utils::BOMB_TEXTURE);




#pragma region ENTITY TO MOVE

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
            _typeEntity = TypeEntity::briquesDestructible;
        }
        else {
            _typeEntity = TypeEntity::briques;
        }

    }

    void update() {
        if (getTypeEntity() == TypeEntity::briquesDestructible) {
            gb.display.drawImage(_x, _y, Utils::BRIQUE_DESTRUCTIBLE);
        }
        else {
            gb.display.drawImage(_x, _y, Utils::BRIQUE_INCASSABLE);
        }
    };
};


class Bombe : public Entity {

public:

    int TimerBombe = General::BombeTimer;
    Color colorBombe = gb.createColor(255, TimerBombe, 38);
    int _indexBombe;
    Players* _PlayerPosingBomb;
    static const int WIDTH = 5;
    static const int HEIGHT = 6;

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
            General::EntityArray[_indexBombe] = NULL;
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
};

#pragma endregion

Players* MyPlayers;
Players* PlayersArrays[3] = { nullptr };

int CompteurEntite = 0;
int CompteurPlayers = 0;

void setup() {
    gb.begin();
    InstanceBreakeableBrique();
    InstanceUnbreakBrique();
    MyPlayers = new Players(General::PlayersStartPositionX, General::PlayersStartPositionY, TypeEntity::players, CompteurPlayers, PlayersImg);
    PlayersArrays[CompteurPlayers++] = MyPlayers;

    //PlayersArrays[CompteurPlayers++] = new Players(71, 8,TypeEntity::Ia, CompteurPlayers, BLUE);

    //PlayersArrays[CompteurPlayers++] = new Players(71, 56,TypeEntity::Ia, CompteurPlayers, RED);

}

void loop() {
    while (!gb.update());
    gb.display.clear();
    DrawBombe(); // on dessine les bombes en premier comme ça elles sont en arriere plan ( passe derriere les murs)
    DrawCadre();
    Draw();
    //Utils::DebugMessageOnTopScreen("NbEntity", CompteurEntite);
    TouchEvent();
    MyPlayers->update();
    //for (Players* joueur : PlayersArrays)
    //{
    //    if (joueur->getType() == TypeEntity::Players) {
    //        continue;
    //    }

    //    if (joueur->PlayersCible == nullptr) 
    //    {
    //        joueur->getCible(PlayersArrays);
    //    }
    //    joueur->update();
    //}
}

void InstanceUnbreakBrique() {
    int EcartBriqueX = Brique::WIDTH * 2;
    int EcartBriqueY = Brique::HEIGHT * 2;

    for (int y = General::LineHeightScore + Brique::HEIGHT; y < 63; y += EcartBriqueY) {
        for (int x = Brique::WIDTH+1; x < 77; x += EcartBriqueX) {
            General::EntityArray[CompteurEntite++] = new Brique(x, y);
        }
    }
}

void InstanceBreakeableBrique() {

    for (int y = 7; y < 63; y += Brique::HEIGHT) 
    {
        for (int x = 1; x <= 75; x += Brique::WIDTH) {

            if (
                    (x == 1 && y == 7) ||
                    (x == 8 && y == 7) ||
                    (x == 64 && y == 7) ||
                    (x == 71 && y == 7) ||
                    (x ==1 && y ==15) ||
                    (x ==71 && y ==15) ||
                    (x == 1 && y == 47) ||
                    (x == 1 && y == 55) ||
                    (x == 71 && y == 55) ||
                    (x == 8 && y == 55) ||
                    (x == 64 && y == 55) ||
                    (x == 71 && y == 55) 
                )
            {
                continue;
            }
            General::EntityArray[CompteurEntite++] = new Brique(x, y, true);
        }
    }
}


void Draw() {
    for (Entity* entity : General::EntityArray) {
        if (entity == nullptr) {
            continue;
        }
        if (entity->getTypeEntity() != TypeEntity::bombes)
        {
            entity->update();
        }
    }
}

void DrawBombe() {
    for (Entity* entity : General::EntityArray) {
        if (entity == nullptr) {
            continue;
        }
        if (entity->getTypeEntity() == TypeEntity::bombes)
        {
            entity->update();
        }
    }
}


void TouchEvent() {

    if (gb.buttons.pressed(BUTTON_UP)) {
        MyPlayers->Move(positionMove::UP);
        //PlayersImg.setFrame(2);
    }

    if (gb.buttons.pressed(BUTTON_DOWN)) {
        MyPlayers->Move(positionMove::DOWN);
        //PlayersImg.setFrame(0);
    }

    if (gb.buttons.pressed(BUTTON_LEFT)) {
        MyPlayers->Move(positionMove::LEFT);
        //PlayersImg.setFrame(3);
    }

    if (gb.buttons.pressed(BUTTON_RIGHT)) {
        MyPlayers->Move(positionMove::RIGHT);
        //PlayersImg.setFrame(1);
    }

    if (gb.buttons.pressed(BUTTON_A)) {
        if (MyPlayers->BombePosingNumber == Players::PlayersMaxBombe) {
            return;
        }

        General::EntityArray[CompteurEntite] = new Bombe(MyPlayers->getX(), MyPlayers->getY(), CompteurEntite, MyPlayers);

        CompteurEntite++;
        if (CompteurEntite >= General::maxEntite)
        {
            CompteurEntite = 0;
        }
        MyPlayers->BombePosingNumber++;
    }
}

void DrawCadre() {
    gb.display.setColor(GRAY);
    gb.display.fillRect(0, 0, gb.display.width(), 7);
    gb.display.drawFastVLine(0, 0, gb.display.height());
    gb.display.drawFastVLine(79, 0, gb.display.height());
}

