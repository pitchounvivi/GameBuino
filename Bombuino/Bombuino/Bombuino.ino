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
#include <Gamebuino-Meta.h>
#include <cstdlib>


Image PlayersImg(Utils::ROBOT_TEXTURE);
Players* PlayersArrays[3] = { nullptr };

void setup() {
    gb.begin();
    General::InstanceBreakeableBrique();
    General::InstanceUnbreakBrique();
    PlayersArrays[General::CompteurPlayers++] = new Players(General::MyPlayerStartPositionX, General::MyPlayerStartPositionY, TypeEntity::players, General::CompteurPlayers, PlayersImg);

    /*PNJ*/
    PlayersArrays[General::CompteurPlayers++] = new Players(71, 8,TypeEntity::Ia, General::CompteurPlayers, PlayersImg, BLUE);
    PlayersArrays[General::CompteurPlayers++] = new Players(71, 56,TypeEntity::Ia, General::CompteurPlayers, PlayersImg, RED);

}

void loop() {
    while (!gb.update());
    gb.display.clear();

    General::DrawBombe();
    General::DrawCadre();
    General::DrawEntities();
    TouchEvent();
    //PlayersArrays[0]->update();

    for (Players* joueur : PlayersArrays)
    {

        if (joueur->PlayersCible == nullptr && joueur->getType() != TypeEntity::players)
        {
            joueur->getCible(PlayersArrays);
        }
        joueur->update();
    }
}

/// <summary>
/// Capte les touches de notre joueur
/// </summary>
void TouchEvent() {

    if (gb.buttons.pressed(BUTTON_UP)) {
        PlayersArrays[0]->Move(positionMove::UP);
        //PlayersImg.setFrame(2);
    }

    if (gb.buttons.pressed(BUTTON_DOWN)) {
        PlayersArrays[0]->Move(positionMove::DOWN);
        //PlayersImg.setFrame(0);
    }

    if (gb.buttons.pressed(BUTTON_LEFT)) {
        PlayersArrays[0]->Move(positionMove::LEFT);
        //PlayersImg.setFrame(3);
    }

    if (gb.buttons.pressed(BUTTON_RIGHT)) {
        PlayersArrays[0]->Move(positionMove::RIGHT);
        //PlayersImg.setFrame(1);
    }

    if (gb.buttons.pressed(BUTTON_A)) {
        //Bombe::PoseBombe(PlayersArrays[0]);
    }
}
