// 
// 
// 

#include "General.h"
const int General::FPS = 40;

int General::PlayerStartPositionX = 1;
int General::PlayerStartPositionY = 16;


int General::LineHeightScore = 7;

// Cette valeur sert pour la couleurs de la bombe
// qui varie et une fois arriv� � 0 signifiez que la bombe explose
// x6 car on on d�cr�mente de 2 
const int General::BombeTimer= General::FPS*6; 
