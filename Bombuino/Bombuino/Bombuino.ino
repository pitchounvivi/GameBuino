/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "General.h"
#include "Entity.h"
#include "Utils.h"
#include <Gamebuino-Meta.h>
#include <cstdlib>
#include "C:/Users/Jack Salon/Desktop/arduino1.8.5-Windows/arduino/portable/sketchbook/libraries/Gamebuino_META/src/utility/Graphics/Graphics.h"

const uint16_t ROBOT_TEXTURE[] = {
    // metadata

    5,      // frame width
    6,      // frame height
    1,      // frames
    0,      // frame loop
    0xf81f, // transparent color
    0,      // 16-bits color mode

    // colormap

    0xf81f, 0x69ec, 0x69ab, 0x69ab, 0xf81f,
    0x522e, 0x91ca, 0x522d, 0x9188, 0x498a,
    0xf81f, 0x41ac, 0x522d, 0x4169, 0xf81f,
    0x69ec, 0x4148, 0x4148, 0x4948, 0x61ab,
    0x71c9, 0x4948, 0x4929, 0x5148, 0x6969,
    0xf81f, 0x39ed, 0xf81f, 0x420d, 0xf81f
}; 

Image PlayerImg(ROBOT_TEXTURE);


const int maxEntite = 300;
Entity* EntityArray[maxEntite] = { nullptr };


#pragma region ENTITY TO MOVE

class Brique : public Entity {
public:

    static const int WIDTH = 7;
    static const int HEIGHT = 8;
     
    TypeEntity typeEntity;
    Brique(int x, int y) 
    {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        typeEntity = TypeEntity::briques;
    }

    void update() {
         gb.display.setColor(BROWN);
         gb.display.fillRect(_x, _y, _width, _height);
    };
};

enum positionMove
{
    UP = -8,
    DOWN = 8,
    LEFT = -7,
    RIGHT = 7,
};


class Player : Entity {
public:
    TypeEntity typeEntity = TypeEntity::players;

    static const int WIDTH = 5;
    static const int HEIGHT = 6;
    static const int PlayerMaxBombe = 2;

    int BombePosingNumber = 0;

    Player(int x, int y, int width, int height) {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        gb.display.fillRect(_x, _y, _width, _height);
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

    void update(positionMove move) {
        switch (move)
        {
        case positionMove::DOWN:
            _y += DOWN;
            break;
        case positionMove::LEFT:
            _x += LEFT;
            break;
        case positionMove::RIGHT:
            _x += RIGHT;
            break;
        case positionMove::UP:
            _y += UP;
            break;
        default:
            break;
        }
    }

    void update() {
        //gb.display.setColor(WHITE);
        //gb.display.fillRect(_x, _y, _width, _height);
        gb.display.drawImage(_x, _y, PlayerImg);
    }

};

Image Explosion(Utils::EXPLOSION_TEXTURE);
class Bombe : public Entity {

public:
    TypeEntity typeEntity = TypeEntity::bombes;

    int TimerBombe = General::BombeTimer;
    Color colorBombe = gb.createColor(255, TimerBombe, 38);
    int _indexBombe;
    Player* _playerPosingBomb;
    static const int WIDTH = 5;
    static const int HEIGHT = 6;

    Bombe(int x, int y,int indexBombe,Player* playerPoseBombe) {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        _indexBombe = indexBombe;
        _playerPosingBomb = playerPoseBombe;
    };

    int testctp = 0;
    void update() {

        Utils::DebugMessageOnTopScreen("TimerBombe", TimerBombe);
        if (TimerBombe < 14) {
            gb.display.drawImage(_x-Brique::WIDTH, _y-Brique::HEIGHT, Explosion);
            Explosion.setFrame(1);
            gb.display.drawImage(_x - Brique::WIDTH, _y - Brique::HEIGHT, Explosion);

        }
        else {
            gb.display.drawImage(_x, _y, Utils::BOMB_TEXTURE);
        }


        if (TimerBombe <= 0) {
            EntityArray[_indexBombe] = NULL;
            _playerPosingBomb->BombePosingNumber--;

            if (_playerPosingBomb->BombePosingNumber <= 0) {
                _playerPosingBomb->BombePosingNumber = 0;
            }

            return;
        }
        colorBombe = gb.createColor(255, TimerBombe, 38);
        TimerBombe -= 2;
    }
};
#pragma endregion

Player* player;
int CompteurEntite = 0;

void setup() {
    gb.begin();
    InstanceUnbreakBrique();
    player = new Player(General::PlayerStartPositionX,General::PlayerStartPositionY, Player::WIDTH,Player::HEIGHT);
}

void loop() {
    while (!gb.update());
    gb.display.clear();
    gb.display.drawFastHLine(0, General::LineHeightScore, gb.display.width());
    Draw();
    TouchEvent();
    player->update();
}

void InstanceUnbreakBrique() {
    int EcartBriqueX = Brique::WIDTH *2 ;
    int EcartBriqueY = Brique::HEIGHT * 2;

    for (int y = General::LineHeightScore + Brique::HEIGHT; y < 63; y += EcartBriqueY) {
        for (int x = Brique::WIDTH; x < 77; x += EcartBriqueX) {
            EntityArray[CompteurEntite++] = new Brique(x, y);
        }
    }
}


void Draw() {
    for (Entity* entity : EntityArray) {
        if (entity == nullptr) {
            continue;
        }
        entity->update();
    }
}


void TouchEvent() {

    if (gb.buttons.pressed(BUTTON_UP)) {
        if (!PlayerCanMove(positionMove::UP)) {
            return;
        }
        player->update(positionMove::UP);
        //PlayerImg.setFrame(2);
    }

    if (gb.buttons.pressed(BUTTON_DOWN)) {
        if (!PlayerCanMove(positionMove::DOWN)) {
            return;
        }

        player->update(positionMove::DOWN);
        //PlayerImg.setFrame(0);
    }

    if (gb.buttons.pressed(BUTTON_LEFT)) {
        if (!PlayerCanMove(positionMove::LEFT)) {
            return;
        }
        player->update(positionMove::LEFT);
        //PlayerImg.setFrame(3);
    }

    if (gb.buttons.pressed(BUTTON_RIGHT)) {
        if (!PlayerCanMove(positionMove::RIGHT)) {
            return;
        }
        player->update(positionMove::RIGHT);
        //PlayerImg.setFrame(1);
    }    
    
    if (gb.buttons.pressed(BUTTON_A)) {
        if (player->BombePosingNumber == Player::PlayerMaxBombe) {
            return;
        }

        EntityArray[CompteurEntite] = new Bombe(player->getX(), player->getY(), CompteurEntite,player);

        CompteurEntite++;
        if (CompteurEntite >= maxEntite)
        {
            CompteurEntite = 0;
        }
        player->BombePosingNumber++;
    }
}

/// <summary>
/// Méthode qui va tester si le joueur entre en collision avec une brique
/// ( on pourrait améliorer la méthode de recherche en indexant chaque brique et rechercher sur l'index ( lettre pour les lignes et 
/// </summary>
/// <param name="moveTO"></param>
/// <returns></returns>
bool PlayerCanMove(positionMove moveTO){
    bool tmp = true;

    if (moveTO == positionMove::LEFT || moveTO == positionMove::RIGHT)
    {
        // si on sort de l'écran
        if (player->getX() + moveTO <= 0 || player->getX() + moveTO >= 77) {
            return false;
        }
        gb.display.setCursor(0, 0);
        gb.display.setColor(YELLOW);

        // si la position du joueur + ou - X entre en collision avec une entity alors il ne bouge pas
        for (Entity* entity : EntityArray) {

            if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), player->getX() + moveTO, player->getY(), player->getWidth(), player->getHeight())) {
                tmp = false;
            }
        }

    }
    else {

        if (player->getY() + moveTO <= 7 || player->getY() + moveTO >=63) {
            return false;
        }

        // si la position du joueur + ou - Y entre en collision avec une entity alors il ne bouge pas
        for (Entity* entity : EntityArray) {
            if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), player->getX(), player->getY() + moveTO, player->getWidth(), player->getHeight())) {
                tmp = false;
            }
        }
    }

    return tmp;
}



