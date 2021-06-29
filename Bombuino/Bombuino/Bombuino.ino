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
    General::players.push(new Players(General::MY_PLAYER_START_POSITION_X, General::MY_PLAYER_START_POSITION_Y, TypeEntity::players, General::CompteurPlayers, PlayersImg));
    
    /*PNJ*/
    General::players.push(new Players(71, 8,TypeEntity::Ia, General::CompteurPlayers, PlayersImg, BLUE));
    //General::PlayersArrays[General::CompteurPlayers++] = new Players(71, 56,TypeEntity::Ia, General::CompteurPlayers, PlayersImg, RED);

}

void loop() {
    while (!gb.update());
    TouchEvent();
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


/// <summary>
/// Capte les touches de notre joueur
/// </summary>
void TouchEvent() {
    Players* MyPlayer = (Players*) General::players.find(0);

    if (gb.buttons.pressed(BUTTON_UP)) {
        MyPlayer->Move(MOVES::UP);
        //PlayersImg.setFrame(2);
    }

    if (gb.buttons.pressed(BUTTON_DOWN)) {
        MyPlayer->Move(MOVES::DOWN);
        //PlayersImg.setFrame(0);
    }

    if (gb.buttons.pressed(BUTTON_LEFT)) {
        MyPlayer->Move(MOVES::LEFT);
        //PlayersImg.setFrame(3);
    }

    if (gb.buttons.pressed(BUTTON_RIGHT)) {
        MyPlayer->Move(MOVES::RIGHT);
        //PlayersImg.setFrame(1);
    }

    if (gb.buttons.pressed(BUTTON_A)) {
        MyPlayer->PoseBombe();
    }    
    if (gb.buttons.pressed(BUTTON_B)) {
        General::Pause = false;
    }

}
