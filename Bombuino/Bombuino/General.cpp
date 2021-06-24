// 
// 
// 

#include "General.h"
const int General::FPS = 40;

int General::PlayersStartPositionX = 2;
int General::PlayersStartPositionY = 7;


int General::LineHeightScore = 7;


// Bombe dure 2s
const int General::BombeTimer= General::FPS*2; 

Entity* General::EntityArray[300] = { nullptr };