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

class Brique : public Entity {
public:

    static const int WIDTH = 7;
    static const int HEIGHT = 8;
     
    TypeEntity typeEntity;
    Brique(int x, int y) 
    {
        _x = x;
        _y = y;

        typeEntity = TypeEntity::briques;
    }

    void update() {
         gb.display.setColor(BROWN);
         gb.display.fillRect(_x, _y, WIDTH, HEIGHT);
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
    Player(int x, int y, int width, int height) {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
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
        gb.display.setColor(WHITE);
        gb.display.fillRect(_x, _y, _width, _height);
    }

};

class Bombe : public Entity {

public:
    TypeEntity typeEntity = TypeEntity::bombes;
    int TimerBombe = General::BombeTimer;
    Color colorBombe = gb.createColor(255, TimerBombe, 38);
    int _indexBombe;
    Bombe(int x, int y,int indexBombe) {
        _x = x;
        _y = y;
        _width = General::PlayerWidth;
        _height = General::PlayerHeight;
        _indexBombe = indexBombe;
    };

    void update(Entity* entityARRAY[]) {

        if (TimerBombe <= 0) {
            entityARRAY[_indexBombe] = NULL;
            return;
        }
        colorBombe = gb.createColor(255, TimerBombe, 38);
        TimerBombe-=2;

    }   

    void update() {
        update(EntityArray);
        gb.display.setColor(colorBombe);
        gb.display.fillRoundRect(_x, _y, _width, _height,5);
    }
};

//Bombe* BombeArray[20];
//Brique* briqueArray[99];

Player* player;
Entity* EntityArray[50] = {nullptr};
int cptEntite = 0;

int EntityCompteur = 0;
int cptBrique = 0;
int cptBriquePrint = 0;

void setup() {
    gb.begin();
    InstanceUnbreakBrique();
    player = new Player(General::PlayerStartPositionX,General::PlayerStartPositionY, General::PlayerWidth,General::PlayerHeight);
}

void loop() {
    while (!gb.update());
    gb.display.clear();

    Utils::DebugMessageOnTopScreen("brique", cptBrique);
    Utils::DebugMessageOnBottomScreen("briquef", cptBriquePrint);
    gb.display.drawFastHLine(0, General::LineHeightScore, gb.display.width());

    Draw();
    TouchEvent();
    player->update();

}

void InstanceUnbreakBrique() {
    int EcartBriqueX = Brique::WIDTH *2 ;
    int EcartBriqueY = Brique::HEIGHT * 2;

    //for (int y = General::LineHeightScore + General::HeightBrique; y < 63; y += EcartBriqueY) {
        for (int x = Brique::WIDTH; x < 77; x += EcartBriqueX) {
            EntityArray[cptEntite] = new Brique(x, 15);
            cptEntite += 1;
            cptBrique++;
        }
    //}
}


void Draw() {
    cptBriquePrint = 0;
    gb.display.setCursor(1, 8);
    for (Entity* entity : EntityArray) {
        if (entity == nullptr) {
            continue;
        }
        gb.display.printf("%d\n",entity->typeEntity);

        entity->update();
        cptBriquePrint++;
        //if (entity->typeEntity == TypeEntity::briques) {
        //    Brique* brique = (Brique*)entity;

        //    cptBriquePrint++;
        //}

        //if (entity->typeEntity == TypeEntity::bombes) {
        //    Bombe* bombe = static_cast<Bombe*>(entity);
        //    bombe->update(EntityArray);
        //    gb.display.setColor(bombe->colorBombe);
        //    gb.display.fillRoundRect(bombe->getX(), bombe->getY(), bombe->getWidth(), bombe->getHeight(), 5);
        //}

    }
}


void TouchEvent() {

    if (gb.buttons.pressed(BUTTON_UP)) {
        if (!PlayerCanMove(positionMove::UP)) {
            return;
        }
        player->update(positionMove::UP);
    }

    if (gb.buttons.pressed(BUTTON_DOWN)) {
        if (!PlayerCanMove(positionMove::DOWN)) {
            return;
        }

        player->update(positionMove::DOWN);
    }

    if (gb.buttons.pressed(BUTTON_LEFT)) {
        if (!PlayerCanMove(positionMove::LEFT)) {
            return;
        }
        player->update(positionMove::LEFT);
    }

    if (gb.buttons.pressed(BUTTON_RIGHT)) {
        if (!PlayerCanMove(positionMove::RIGHT)) {
            return;
        }
        player->update(positionMove::RIGHT);
    }    
    
    if (gb.buttons.pressed(BUTTON_A)) {
        EntityArray[EntityCompteur] = new Bombe(player->getX(), player->getY(), EntityCompteur);

        EntityCompteur++;
        if (EntityCompteur >= 300)
        {
            EntityCompteur = 0;
        }

        Utils::DebugMessageOnBottomScreen("EntityCompteur", EntityCompteur);
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


        // si la position du joueur + ou - X entre en collision avec une brique alors il ne bouge pas
        for (Entity* brique : EntityArray) {
            if (gb.collide.rectRect(brique->getX(), brique->getY(), brique->getWidth(), brique->getHeight(), player->getX() + moveTO, player->getY(), player->getWidth(), player->getHeight())) {
                tmp = false;
            }
        }
        return tmp;
    }
    else {

        if (player->getY() + moveTO <= 7 || player->getY() + moveTO >=63) {
            return false;
        }


        // si la position du joueur + ou - Y entre en collision avec une brique alors il ne bouge pas
        for (Entity* brique : EntityArray) {
            if (gb.collide.rectRect(brique->getX(), brique->getY(), brique->getWidth(), brique->getHeight(), player->getX(), player->getY() + moveTO, player->getWidth(), player->getHeight())) {
                tmp = false;
            }
        }
        return tmp;
    }
}