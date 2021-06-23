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
#include "C:\Users\fabrice ferrere\Desktop\arduino1.8.5-Windows\arduino\portable\sketchbook\libraries\Gamebuino_META\src\utility\Graphics/Graphics.h"


Image PlayerImg(Utils::ROBOT_TEXTURE);
Image Explosion(Utils::EXPLOSION_TEXTURE);
Image BombeImg(Utils::BOMB_TEXTURE);
const int maxEntite = 300;
Entity* EntityArray[maxEntite] = { nullptr };




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

enum positionMove
{
    UP = -8,
    DOWN = 8,
    LEFT = -7,
    RIGHT = 7,
};

class Player : Entity {
public:
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
        _typeEntity = TypeEntity::players;
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

class Bombe : public Entity {

public:

    int TimerBombe = General::BombeTimer;
    Color colorBombe = gb.createColor(255, TimerBombe, 38);
    int _indexBombe;
    Player* _playerPosingBomb;
    static const int WIDTH = 5;
    static const int HEIGHT = 6;

    Bombe(int x, int y, int indexBombe, Player* playerPoseBombe) {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        _indexBombe = indexBombe;
        _playerPosingBomb = playerPoseBombe;
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
            EntityArray[_indexBombe] = NULL;
            _playerPosingBomb->BombePosingNumber--;

            if (_playerPosingBomb->BombePosingNumber <= 0) {
                _playerPosingBomb->BombePosingNumber = 0;
            }
            checkBombeAlentour();
            return;
        }
        colorBombe = gb.createColor(255, TimerBombe, 38);
        TimerBombe -= 1;
    }

    void checkBombeAlentour()
    {

        for (int i = 0;i < maxEntite; i++)
        {
            if (EntityArray[i] == nullptr) 
            {
                continue;
            }
            Entity* tmp = EntityArray[i];

            // Je suis une brique ou un players ?
            if (tmp->getTypeEntity() == TypeEntity::briquesDestructible || tmp->getTypeEntity() == TypeEntity::players)
            {

                // Collision avec le carré  de droite ?
                if (gb.collide.rectRect(_x + positionMove::RIGHT, _y, Bombe::WIDTH, Bombe::HEIGHT, tmp->getX(), tmp->getY(), tmp->getWidth(), tmp->getHeight()))
                {
                    // si c'est mon joueur 

                    // si c'est une brique ou une IA:
                    EntityArray[i] = nullptr;
                }
                // Collision avec le carré de gauche? 
                if (gb.collide.rectRect(_x + positionMove::LEFT, _y, Bombe::WIDTH, Bombe::HEIGHT, tmp->getX(), tmp->getY(), tmp->getWidth(), tmp->getHeight()))
                {
                    EntityArray[i] = nullptr;
                }
                // Collision avec le carré d'en haut?
                if (gb.collide.rectRect(_x, _y + positionMove::UP, Bombe::WIDTH, Bombe::HEIGHT, tmp->getX(), tmp->getY(), tmp->getWidth(), tmp->getHeight()))
                {
                    EntityArray[i] = nullptr;
                }
                // si collision avec le carré du bas 
                if (gb.collide.rectRect(_x, _y + positionMove::DOWN, Bombe::WIDTH, Bombe::HEIGHT, tmp->getX(), tmp->getY(), tmp->getWidth(), tmp->getHeight()))
                {
                    EntityArray[i] = nullptr;
                }
            }


        }
    }
};
#pragma endregion


Player* player;
int CompteurEntite = 0;

void setup() {
    gb.begin();
    InstanceBreakeableBrique();
    InstanceUnbreakBrique();
    player = new Player(General::PlayerStartPositionX, General::PlayerStartPositionY, Player::WIDTH, Player::HEIGHT);
}

void loop() {
    while (!gb.update());
    gb.display.clear();
    DrawBombe(); // on dessine les bombes en premier comme ça elles sont en arriere plan ( passe derriere les murs)
    DrawCadre();
    Draw();
    Utils::DebugMessageOnTopScreen("NbEntity", CompteurEntite);
    TouchEvent();
    player->update();
}

void InstanceUnbreakBrique() {
    int EcartBriqueX = Brique::WIDTH * 2;
    int EcartBriqueY = Brique::HEIGHT * 2;

    for (int y = General::LineHeightScore + Brique::HEIGHT; y < 63; y += EcartBriqueY) {
        for (int x = Brique::WIDTH+1; x < 77; x += EcartBriqueX) {
            EntityArray[CompteurEntite++] = new Brique(x, y);
        }
    }
}

void InstanceBreakeableBrique() {

    //for (int y = 0; y < 63; y += Brique::HEIGHT) {
    //    for (int x = 0; x < 77; x += Brique::WIDTH) {
    //        EntityArray[CompteurEntite++] = new Brique(x, y,true);
    //    }
    //}
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
            EntityArray[CompteurEntite++] = new Brique(x, y, true);
        }
    }
}


void Draw() {
    for (Entity* entity : EntityArray) {
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
    for (Entity* entity : EntityArray) {
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

        EntityArray[CompteurEntite] = new Bombe(player->getX(), player->getY(), CompteurEntite, player);

        CompteurEntite++;
        if (CompteurEntite >= maxEntite)
        {
            CompteurEntite = 0;
        }
        player->BombePosingNumber++;
    }
}

void DrawCadre() {
    gb.display.setColor(GRAY);
    gb.display.fillRect(0, 0, gb.display.width(), 7);
    gb.display.drawFastVLine(0, 0, gb.display.height());
    gb.display.drawFastVLine(79, 0, gb.display.height());
}


/// <summary>
/// Méthode qui va tester si le joueur entre en collision avec une brique
/// ( on pourrait améliorer la méthode de recherche en indexant chaque brique et rechercher sur l'index ( lettre pour les lignes et 
/// </summary>
/// <param name="moveTO"></param>
/// <returns></returns>
bool PlayerCanMove(positionMove moveTO) {
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

        if (player->getY() + moveTO <= 7 || player->getY() + moveTO >= 63) {
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
