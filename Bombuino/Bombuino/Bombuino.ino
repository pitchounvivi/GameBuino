/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "General.h"
#include "Entity.h"
#include "Utils.h"
#include <Gamebuino-Meta.h>
#include <./Graphics/Graphics.h>
#include <cstdlib>



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
    Player* PlayerCible =nullptr;
    int IndexPlayer;
    Color colorPlayer;

    Player(int x, int y,TypeEntity typeEntity,int indexPlayer,const Color colorIA = WHITE) {
        _x = x;
        _y = y;
        _width = WIDTH;
        _height = HEIGHT;
        IndexPlayer = indexPlayer;
        _typeEntity = typeEntity;

        if (typeEntity == TypeEntity::Ia) 
        {
            colorPlayer = colorIA;
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

    void getCible(Player* PlayersArray[])
    {
        int cibleInt = IndexPlayer;
        while (cibleInt == IndexPlayer) 
        {
            cibleInt = rand() % 3;
        }
        PlayerCible = PlayersArray[cibleInt];
    }

    void update() {
        if (getTypeEntity() == TypeEntity::Ia)
        {
            gb.display.setColor(colorPlayer);
            gb.display.fillCircle(_x, _y, 2);
            DebugPnj();

            /*======================== GESTION DEPLACEMENT HAUT BAS =======================*/
            //  pnj va en haut sinon il va en bas


                
                // si pas d'obstacle avance 
                // si rencontre un bloc pose une bombe. 


            /*======================== GESTION DEPLACEMENT COTÉ =======================*/
            // si le x du joueur cible est plus petit que moi 
            // je vais a gauche sinon a droite

                // si pas d'obstacle avance 
                // si rencontre un bloc pose une bombe. 
        }
        else 
        {
            gb.display.drawImage(_x, _y, PlayerImg);
        }

    }

    void DebugPnj() {
        gb.display.drawCircle(PlayerCible->getX(), PlayerCible->getY(),5);
        gb.display.print(IndexPlayer);
        gb.display.print(".");
        gb.display.print(PlayerCible->IndexPlayer);
        gb.display.print("-");
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

Player* MyPlayer;
Player* PlayersArrays[3] = { nullptr };

int CompteurEntite = 0;
int CompteurPlayer = 0;

void setup() {
    gb.begin();
    InstanceBreakeableBrique();
    InstanceUnbreakBrique();
    MyPlayer = new Player(General::PlayerStartPositionX, General::PlayerStartPositionY, TypeEntity::players, CompteurPlayer);
    PlayersArrays[CompteurPlayer++] = MyPlayer;

    //PlayersArrays[CompteurPlayer++] = new Player(71, 8,TypeEntity::Ia, CompteurPlayer, BLUE);

    //PlayersArrays[CompteurPlayer++] = new Player(71, 56,TypeEntity::Ia, CompteurPlayer, RED);

}

void loop() {
    while (!gb.update());
    gb.display.clear();
    DrawBombe(); // on dessine les bombes en premier comme ça elles sont en arriere plan ( passe derriere les murs)
    DrawCadre();
    Draw();
    //Utils::DebugMessageOnTopScreen("NbEntity", CompteurEntite);
    TouchEvent();
    MyPlayer->update();
    //for (Player* joueur : PlayersArrays)
    //{
    //    if (joueur->getType() == TypeEntity::players) {
    //        continue;
    //    }

    //    if (joueur->PlayerCible == nullptr) 
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
            EntityArray[CompteurEntite++] = new Brique(x, y);
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
        MyPlayer->Move(positionMove::UP);
        //PlayerImg.setFrame(2);
    }

    if (gb.buttons.pressed(BUTTON_DOWN)) {
        if (!PlayerCanMove(positionMove::DOWN)) {
            return;
        }

        MyPlayer->Move(positionMove::DOWN);
        //PlayerImg.setFrame(0);
    }

    if (gb.buttons.pressed(BUTTON_LEFT)) {
        if (!PlayerCanMove(positionMove::LEFT)) {
            return;
        }
        MyPlayer->Move(positionMove::LEFT);
        //PlayerImg.setFrame(3);
    }

    if (gb.buttons.pressed(BUTTON_RIGHT)) {
        if (!PlayerCanMove(positionMove::RIGHT)) {
            return;
        }
        MyPlayer->Move(positionMove::RIGHT);
        //PlayerImg.setFrame(1);
    }

    if (gb.buttons.pressed(BUTTON_A)) {
        if (MyPlayer->BombePosingNumber == Player::PlayerMaxBombe) {
            return;
        }

        EntityArray[CompteurEntite] = new Bombe(MyPlayer->getX(), MyPlayer->getY(), CompteurEntite, MyPlayer);

        CompteurEntite++;
        if (CompteurEntite >= maxEntite)
        {
            CompteurEntite = 0;
        }
        MyPlayer->BombePosingNumber++;
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
        if (MyPlayer->getX() + moveTO <= 0 || MyPlayer->getX() + moveTO >= 77) {
            return false;
        }
        gb.display.setCursor(0, 0);
        gb.display.setColor(YELLOW);

        // si la position du joueur + ou - X entre en collision avec une entity alors il ne bouge pas
        for (Entity* entity : EntityArray) {

            if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), MyPlayer->getX() + moveTO, MyPlayer->getY(), MyPlayer->getWidth(), MyPlayer->getHeight())) {
                tmp = false;
            }
        }

    }
    else {

        if (MyPlayer->getY() + moveTO < 7 || MyPlayer->getY() + moveTO >= 63) {
            return false;
        }

        // si la position du joueur + ou - Y entre en collision avec une entity alors il ne bouge pas
        for (Entity* entity : EntityArray) {
            if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), MyPlayer->getX(), MyPlayer->getY() + moveTO, MyPlayer->getWidth(), MyPlayer->getHeight())) {
                tmp = false;
            }
        }
    }

    return tmp;
}
