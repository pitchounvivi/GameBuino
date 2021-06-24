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
    //General::PlayersArrays[General::CompteurPlayers++] = new Players(71, 8,TypeEntity::Ia, General::CompteurPlayers, BLUE);
    //General::PlayersArrays[General::CompteurPlayers++] = new Players(71, 56,TypeEntity::Ia, General::CompteurPlayers, RED);

}

void loop() {
    while (!gb.update());
    gb.display.clear();

    General::DrawBombe();
    General::DrawCadre();
    General::DrawEntities();
    TouchEvent();
    PlayersArrays[0]->update();

    //for (Players* joueur : General::PlayersArrays)
    //{
    //    if (joueur->getType() == TypeEntity::Players) {
    //        continue;
    //    }

    //    if (joueur->PlayersCible == nullptr) 
    //    {
    //        joueur->getCible(General::PlayersArrays);
    //    }
    //    joueur->update();
    //}
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
        // ai-je posé le max de bombe?
        if (PlayersArrays[0]->BombePosingNumber == Players::PlayersMaxBombe) {
            return;
        }

        General::EntityArray[General::CompteurEntite] = new Bombe(PlayersArrays[0]->getX(), PlayersArrays[0]->getY(), General::CompteurEntite, PlayersArrays[0]);

        General::CompteurEntite++;
        if (General::CompteurEntite >= General::maxEntite)
        {
            General::CompteurEntite = 0;
        }
        PlayersArrays[0]->BombePosingNumber++;
    }
}

