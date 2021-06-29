// 
// 
// 

#include "Bombe.h"
#include "Players.h"

void Bombe::update() {
    if (TimerBombe <= 14) {
        gb.display.drawImage(_x - Brique::WIDTH - 1, _y - Brique::HEIGHT - 1, explo_texture);
    } else {
        gb.display.drawImage(_x, _y, bombe_texture);
    }
    if (TimerBombe <= 0) {
        checkBombeAlentour();
        _playerRef->decBombCount();
        //General::entities.remove(this);
        return;
    }
    color = gb.createColor(255, TimerBombe, 38);
    TimerBombe -= 1;
}

Bombe::Bombe(int x, int y, Players* playerRef) {
    _x = x;
    _y = y;
    _width = WIDTH;
    _height = HEIGHT;
    _playerRef = playerRef;
    _typeEntity = TypeEntity::BOMBES;
};

int Bombe::getTimerBombe() {
    return TimerBombe;
}

void Bombe::checkBombeAlentour()
{
    const Node<Entity>* iteratorEntity = General::entities.get_head();

    while (iteratorEntity)
    {
        Entity* ent = iteratorEntity->_current;
        // Je suis une brique ou un Players si oui je check les coord haut bas gauche droite et je delete l'entity
        if (ent->getTypeEntity() == TypeEntity::BRIQUES_BREAK &&
            (gb.collide.rectRect(_x + MOVES::RIGHT, _y, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()) ||
                gb.collide.rectRect(_x + MOVES::LEFT, _y, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()) ||
                gb.collide.rectRect(_x, _y + MOVES::UP, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()) ||
                gb.collide.rectRect(_x, _y + MOVES::DOWN, Bombe::WIDTH, Bombe::HEIGHT, ent->getX(), ent->getY(), ent->getWidth(), ent->getHeight()))) {
            // si c'est une brique
            //iteratorEntity = iteratorEntity->_next;
            //General::entities.remove(ent);
        }
        iteratorEntity = iteratorEntity->_next;
    }

    const Node<Entity>* iterator = (Node<Entity>*)General::players.get_head();


    while (iterator) {
        Entity* player = iterator->_current;

        if (gb.collide.rectRect(_x, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()) ||
            gb.collide.rectRect(_x + MOVES::RIGHT, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()) ||
            gb.collide.rectRect(_x + MOVES::LEFT, _y, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()) ||
            gb.collide.rectRect(_x, _y + MOVES::UP, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight()) ||
            gb.collide.rectRect(_x, _y + MOVES::DOWN, Bombe::WIDTH, Bombe::HEIGHT, player->getX(), player->getY(), player->getWidth(), player->getHeight())) {
            // si c'est une brique
            iterator = iterator->_next;
            General::players.remove((Players*)player);
            continue;
        }
        iterator = iterator->_next;
    }
}