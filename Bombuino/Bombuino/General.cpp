// 
// 
// 

#include "General.h"
#include "Brique.h"

const int General::FPS = 40;

int General::MyPlayerStartPositionX = 2;
int General::MyPlayerStartPositionY = 7;
int General::HeightCadreScore = 7;
int General::PositionZero = 0;
int General::PositionStartDrawX = 1; // on ne dessine pas de 0 , mais de 1 (sauf pour le cadre) car nos calcul nous amène à 77 donc on esdpacez de 1px de chaqué coté. 
int General::PositionEndDrawX = 77;
int General::CompteurEntite = 0;
int General::CompteurPlayers = 0;



/*" Surcharge de la taille de l'écran car on a travailler sur l'écran de 79x63... Rendu compte trop tard"*/
int General::ScreenWidth = 79;
int General::ScreenHeight = 63;

// Bombe dure 2s
int General::BombeTimer= General::FPS*2; 

Entity* General::EntityArray[300] = { nullptr };


/// <summary>
/// Brique incassable 15
/// </summary>
void General::InstanceUnbreakBrique() {
    int EcartBriqueX = Brique::WIDTH * 2;
    int EcartBriqueY = Brique::HEIGHT * 2;

    for (int y = General::HeightCadreScore + Brique::HEIGHT; y < ScreenHeight; y += EcartBriqueY) {
        for (int x = Brique::WIDTH + General::PositionStartDrawX; x < General::PositionEndDrawX; x += EcartBriqueX) {
            General::EntityArray[CompteurEntite++] = new Brique(x, y);
        }
    }
}

/// <summary>
/// Instancie les bloc destructible et gère l'espace nécessaire au départ pour les joueurs
/// </summary>
void General::InstanceBreakeableBrique() {

    for (int y = General::HeightCadreScore; y < General::ScreenHeight; y += Brique::HEIGHT)
    {
        for (int x = General::PositionStartDrawX; x <= General::PositionEndDrawX; x += Brique::WIDTH) {

            if (
                (x == 1 && y == 7) ||
                (x == 8 && y == 7) ||
                (x == 64 && y == 7) ||
                (x == 71 && y == 7) ||
                (x == 1 && y == 15) ||
                (x == 71 && y == 15) ||
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
            General::EntityArray[General::CompteurEntite++] = new Brique(x, y, true);
        }
    }
}

/// <summary>
/// Dessine le cadre du score et autour de l'arène
/// </summary>
void General::DrawCadre() {
    gb.display.setColor(GRAY);
    gb.display.fillRect(General::PositionZero, General::PositionZero, gb.display.width(), General::HeightCadreScore);
    gb.display.drawFastVLine(General::PositionZero, General::PositionZero, gb.display.height());
    gb.display.drawFastVLine(General::ScreenWidth, General::PositionZero, gb.display.height());
    gb.display.drawFastHLine(General::PositionZero, General::ScreenHeight, gb.display.width());
}

/// <summary>
/// Dessine les bombes !
/// les bombes doivent être dessinés en premier comme ça elles sont en arriere plan ( passe derriere les murs)
/// </summary>
void General::DrawBombe() {
    for (Entity* entity : General::EntityArray) {
        if (entity == nullptr) {
            continue;
        }
        if (entity->getTypeEntity() == TypeEntity::bombes)
        {
            entity->update();
        }
    }
}

/// <summary>
/// Dessine toutes les entites sauf les bombes.
/// </summary>
void General::DrawEntities() {
    for (Entity* entity : General::EntityArray) {
        if (entity == nullptr) {
            continue;
        }
        // ne dessine pas les bombes car on les a dessiné avant
        if (entity->getTypeEntity() != TypeEntity::bombes)
        {
            entity->update();
        }
    }
}
