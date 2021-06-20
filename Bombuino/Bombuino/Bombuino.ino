/*
 Name:		Bombuino.ino
 Created:	16/06/2021 15:04:59
 Author:	Viviane NGUYEN - Moussa FOFANA - Fabrice FERRERE
*/

#include "Entity.h"
#include <Gamebuino-Meta.h>
#include <cstdlib>
#include "Ressources.h"
#include "List.h"

List<Image> list = List<Image>();

void setup() {
	gb.begin();
	list.push(new Image(Ressources::ROBOT_TEXTURE));
	list.push(new Image(Ressources::DOG_TEXTURE));
	/*list.push(new Image (Ressources::WOMAN_TEXTURE));
	list.push(new Image (Ressources::ALIEN_TEXTURE));
	list.push(new Image (Ressources::WALLS_TEXTURE));*/
}


// the loop function runs over and over again until power down or reset
int i = 0;

void loop() {
	while (!gb.update());
	const Node<Image>* iterator = list.get_head();
	i = 0;
	gb.display.clear(GRAY);

	while (iterator) {
		gb.display.printf("toto\n");

		for (uint8_t x = 0; x < 6; x += 1) {
			iterator->_current->setFrame(x);
			gb.display.drawImage(x * 7, i * (6 + 5), *(iterator->_current));
		}
		i += 1;
		iterator = iterator->_next;
		gb.display.printf("bobo\n");
	}
	

	
	gb.display.printf("list size = %d\n", list.size());

	if (gb.buttons.pressed(BUTTON_A)) {
		list.pop();
		if (list.get_head() == nullptr) {
			gb.display.print("JE SUIS NUL");
		}
	}
	if (gb.buttons.pressed(BUTTON_B)) {
		list.push(new Image(Ressources::WOMAN_TEXTURE));
	}
}
