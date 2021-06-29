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
Image IaOneImg(Utils::ALIEN_TEXTURE);
Image IaTwoImg(Utils::WOMAN_TEXTURE);
Image IaThreeImg(Utils::DOG_TEXTURE);

void setup() {

    gb.begin();
    General::InstanceBreakeableBrique();
    General::InstanceUnbreakBrique();
    General::PlayersArrays[General::CompteurPlayers++] = new Players(General::MyPlayerStartPositionX, General::MyPlayerStartPositionY, TypeEntity::players, General::CompteurPlayers, PlayersImg);

    /*PNJ*/
    General::PlayersArrays[General::CompteurPlayers++] = new Players(71, 8, TypeEntity::Ia, General::CompteurPlayers, IaOneImg, BLUE);
    General::PlayersArrays[General::CompteurPlayers++] = new Players(71, 56,TypeEntity::Ia, General::CompteurPlayers, IaTwoImg, RED);
    General::PlayersArrays[General::CompteurPlayers++] = new Players(1, 56,TypeEntity::Ia, General::CompteurPlayers, IaThreeImg, RED);

}

void loop() {
    while (!gb.update());
    gb.display.clear();
    TouchEvent();
    General::DrawBombe();
    General::DrawCadre();
    General::DrawEntities();
    gb.display.print(General::generalTexte);
    for (Entity* ent : General::PlayersArrays)
    {
        if (ent == nullptr)
        {
            continue;
        }

        Players* joueur = (Players*)ent;
        joueur->update();
    }

}


/// <summary>
/// Capte les touches de notre joueur
/// </summary>
void TouchEvent() {
    Players* MyPlayer = (Players*)General::PlayersArrays[0];

    if (gb.buttons.pressed(BUTTON_UP)) {
        MyPlayer->Move(positionMove::UP);
    }

    if (gb.buttons.pressed(BUTTON_DOWN)) {
        MyPlayer->Move(positionMove::DOWN);
    }

    if (gb.buttons.pressed(BUTTON_LEFT)) {
        MyPlayer->Move(positionMove::LEFT);
    }

    if (gb.buttons.pressed(BUTTON_RIGHT)) {
        MyPlayer->Move(positionMove::RIGHT);
    }

    if (gb.buttons.pressed(BUTTON_A)) {
        MyPlayer->PoseBombe();
    }
    if (gb.buttons.pressed(BUTTON_B)) {
    }

}