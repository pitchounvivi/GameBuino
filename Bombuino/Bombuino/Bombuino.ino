/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "General.h"
#include "Entity.h"
#include "Players.h"
#include "Utils.h"
#include "Brique.h"
#include "Bombe.h"
#include "MOVES.h"
#include <Gamebuino-Meta.h>
#include <cstdlib>


Image PlayersImg(Utils::ROBOT_TEXTURE);

void setup() {
    gb.begin();
    General::InstanceBreakeableBrique();
    General::InstanceUnbreakBrique();
    General::players.push(new Players(General::MY_PLAYER_START_POSITION_X, General::MY_PLAYER_START_POSITION_Y, TypeEntity::PLAYER, PlayersImg));
    
    /*IA's*/
    General::players.push(new Players(71, 8, TypeEntity::IA, PlayersImg, BLUE));
}

void loop() {
    while (!gb.update());
    gb.display.clear();
    if (General::Pause) {
        gb.display.print(General::generalTexte);
        gb.display.print(General::generalInt);
        gb.display.print(".");
        gb.display.print(General::generalInt2);
        return;
    }
    General::DrawBombe();
    //General::DrawCadre();
    General::DrawEntities();
    Node<Entity>* iteratorP = (Node<Entity> *)General::players.get_head();
    while (iteratorP) {
        iteratorP->_current->update();
        iteratorP = iteratorP->_next;
    }
}
