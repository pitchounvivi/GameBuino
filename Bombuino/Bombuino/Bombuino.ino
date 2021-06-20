/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "Entity.h"
#include <Gamebuino-Meta.h>
#include <cstdlib>

void setup() {
	gb.begin();
}

// pour rappel l'écran actuel fait 79/63

// Initialisation du tableau
// int Brick[i][j] = {};
int i = 0;
int position_x = 1; // pour centrer le quadrillage, on le décalle de 1
int position_y = 7; // Prise en compte de la première ligne


// the loop function runs over and over again until power down or reset
void loop() {
  
	while (!gb.update());
	gb.display.clear();

	//////////////////////////ZONE QUADRILLAGE
	// afficher une ligne de brique
	int largeur = 77;
	int hauteur = 63;

	affiche_Map(largeur, hauteur);
}

void affiche_Map(int largeur, int hauteur) {
	for (position_y = 7; position_y < hauteur; position_y += 8) {
		for (position_x = 1; position_x < largeur; position_x += 7) {
			gb.display.drawRect(position_x, position_y, 7, 8);
		}
	}
}
