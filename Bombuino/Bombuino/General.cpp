// 
// 
// 

#include "General.h"
#include "Brique.h"
#include "Players.h"
#include "Bombe.h"

const int General::FPS = 40;

const int General::MY_PLAYER_START_POSITION_X = 2;
const int General::MY_PLAYER_START_POSITION_Y = 7;
const int General::HEIGHT_CADRE_SCORE = 7;
const int General::POSITION_ZERO = 0;
const int General::POSITION_START_DRAW_X = 1; // on ne dessine pas de 0 , mais de 1 (sauf pour le cadre) car nos calcul nous amène à 77 donc on esdpacez de 1px de chaqué coté. 
const int General::POSITION_END_DRAW_X = 77;

char* General::generalTexte = "";
char* General::generalTexte2 = "";
int General::generalInt = 0;
int General::generalInt2 = 0;

/* Surcharge de la taille de l'écran car on a travailler sur l'écran de 79x63... Rendu compte trop tard 😅*/
const int General::ScreenWidth = 79;
const int General::ScreenHeight = 63;

// Bombe dure 2s
const int General::BOMBE_TIMER= General::FPS*2; 
const static int NB_PLAYER = 3;

List<Entity> General::entities = List<Entity>();

List<Players> General::players = List<Players>();

bool General::Pause = false;


/// <summary>
/// Brique incassable 15
/// </summary>
void General::InstanceUnbreakBrique() {
    int EcartBriqueX = Brique::WIDTH * 2;
    int EcartBriqueY = Brique::HEIGHT * 2;

    for (int y = General::HEIGHT_CADRE_SCORE + Brique::HEIGHT; y < ScreenHeight; y += EcartBriqueY) {
        for (int x = Brique::WIDTH + General::POSITION_START_DRAW_X; x < General::POSITION_END_DRAW_X; x += EcartBriqueX) {
            General::entities.push(new Brique(x, y));
            //General::EntityArray[CompteurEntite++] = ;
        }
    }
}

/// <summary>
/// Instancie les bloc destructible et gère l'espace nécessaire au départ pour les joueurs
/// </summary>
void General::InstanceBreakeableBrique() {

    for (int y = General::HEIGHT_CADRE_SCORE; y < General::ScreenHeight; y += Brique::HEIGHT)
    {
        for (int x = General::POSITION_START_DRAW_X; x <= General::POSITION_END_DRAW_X; x += Brique::WIDTH) {

            if (
                (x == 1 && y == 7) ||
                (x == 8 && y == 7) ||
                (x == 64 && y == 7) ||
                (x == 71 && y == 7) ||
                (x == 1 && y == 15) ||
                (x == 71 && y == 15) ||
                (x == 1 && y == 47) ||
                (x == 1 && y == 55) ||
                (x == 71 && y == 47) ||
                (x == 8 && y == 55) ||
                (x == 64 && y == 55) ||
                (x == 71 && y == 55)
                )
            {
                continue;
            }
            General::entities.push(new Brique(x, y, true));
            //General::EntityArray[General::CompteurEntite++] = new Brique(x, y, true);
        }
    }
}

/// <summary>
/// Dessine le cadre du score et autour de l'arène
/// </summary>
void General::DrawCadre() {
    gb.display.setColor(GRAY);
    gb.display.fillRect(General::POSITION_ZERO, General::POSITION_ZERO, gb.display.width(), General::HEIGHT_CADRE_SCORE);
    gb.display.drawFastVLine(General::POSITION_ZERO, General::POSITION_ZERO, gb.display.height());
    gb.display.drawFastVLine(General::ScreenWidth, General::POSITION_ZERO, gb.display.height());
    gb.display.drawFastHLine(General::POSITION_ZERO, General::ScreenHeight, gb.display.width());
}

/// <summary>
/// Dessine les bombes !
/// les bombes doivent être dessinés en premier comme ça elles sont en arriere plan ( passe derriere les murs)
/// </summary>
void General::DrawBombe() {
    const Node<Entity> *iterator = General::entities.get_head();
    while (iterator) {
        if (iterator->_current->getTypeEntity() == TypeEntity::BOMBES)
        {
            iterator->_current->update();
        }
        iterator = iterator->_next;
    }
}

/// <summary>
/// Dessine toutes les entites sauf les bombes.
/// </summary>
void General::DrawEntities() {
    const Node<Entity>* iterator = General::entities.get_head();
    while (iterator) {
        // ne dessine pas les bombes car on les a dessiné avant
        if (iterator->_current->getTypeEntity() != TypeEntity::BOMBES)
        {
            iterator->_current->update();
        }
        iterator = iterator->_next;
    }
}
