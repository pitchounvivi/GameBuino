/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "Entity.h"
#include <Gamebuino-Meta.h>
#include <cstdlib>
#include "Ressources.h"

void setup() {
	gb.begin();
}

Image robot(Ressources::ROBOT_TEXTURE);
Image woman(Ressources::WOMAN_TEXTURE);
Image dog(Ressources::DOG_TEXTURE);
Image alien(Ressources::ALIEN_TEXTURE);
Image walls(Ressources::WALLS_TEXTURE);

Image* test[] = { &robot , &woman, &dog, &alien };
// the loop function runs over and over again until power down or reset
void loop() {
	while (!gb.update());
	gb.display.clear(GRAY);
	for (int i = 0; i < 4; i += 1) {
		for (uint8_t x = 0; x < 6; x += 1) {
			test[i]->setFrame(x);
			gb.display.drawImage(x * 7, i * (6 + 5), *test[i]);
		}
	}
}
