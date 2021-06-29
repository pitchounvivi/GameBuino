// 
// 
// 

#include "Players.h"
#include "Bombe.h"

void Players::controls() {
	if (getTypeEntity() == TypeEntity::IA) {
		return;
	}

	gb.display.drawImage(_x, _y + 1, img);

	if (gb.buttons.pressed(BUTTON_UP)) {
		move(MOVES::UP);
		//PlayersImg.setFrame(2);
	}

	if (gb.buttons.pressed(BUTTON_DOWN)) {
		move(MOVES::DOWN);
		//PlayersImg.setFrame(0);
	}

	if (gb.buttons.pressed(BUTTON_LEFT)) {
		move(MOVES::LEFT);
		//PlayersImg.setFrame(3);
	}

	if (gb.buttons.pressed(BUTTON_RIGHT)) {
		move(MOVES::RIGHT);
		//PlayersImg.setFrame(1);
	}

	if (gb.buttons.pressed(BUTTON_A)) {
		PoseBombe();
	}

	if (gb.buttons.pressed(BUTTON_B)) {
		General::Pause = false;
	}
}

void Players::controlsIA() {
	if (getTypeEntity() != TypeEntity::IA) {
		return;
	}

	gb.display.setColor(colorPlayers);
	gb.display.fillCircle(_x + 3, _y + 3, 2);
	timerNextMove--;
	if (timerNextMove > 0) {
		return;
	}
	timerNextMove = Utils::randomTimerNextAction();

	posArrayToMoveInSecurity[0] = MOVES::NONE;
	posArrayToMoveInSecurity[1] = MOVES::NONE;

	// je regarde ce qu'il y a sur la case courante:
	TypeEntity typeEntiteInCurrentCase = GetEntityInCurrentCase();

	if (typeEntiteInCurrentCase == TypeEntity::BOMBES)
	{
		iaCalcSecurePlaces();
		move(posArrayToMoveInSecurity[0]);
		move(posArrayToMoveInSecurity[1]);
		return;
	}

	if (this->BombePosingNumber != 0) {
		return;
	}

	MOVES pmvTmp = GetEmptyCaseBetweenIa();

	if (pmvTmp != NONE)
	{
		move(pmvTmp);
	}
	if (Action(UP))
	{
		return;
	}
	if (Action(DOWN))
	{
		return;
	}
	if (Action(LEFT))
	{
		return;
	}
	if (Action(RIGHT))
	{
		return;
	}
}

Players::Players(int x, int y, TypeEntity typeEntity, Image image, const Color colorIA) {
	_x = x;
	_y = y;
	_typeEntity = typeEntity;
	img = image;
	if (typeEntity == TypeEntity::IA) {
		colorPlayers = colorIA;
	}
}

void Players::PoseBombe() {
	if (this->BombePosingNumber == Players::PlayersMaxBombe) {
		return;
	}
	this->BombePosingNumber++;
	Bombe* bombe = new Bombe(this->getX(), this->getY(), this);
	General::entities.push(bombe);
}

void Players::decBombCount() {
	BombePosingNumber -= 1;
	if (BombePosingNumber <= 0) {
		BombePosingNumber = 0;
	}
}