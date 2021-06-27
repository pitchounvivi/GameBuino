

#ifndef _Players_h
#define _Players_h
#pragma once

#include <Gamebuino-Meta.h>
#include "Utils.h"
#include "General.h"
#include "Entity.h"
#include "Bombe.h"


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
enum positionMove
{
	UP = -8,
	DOWN = 8,
	LEFT = -7,
	RIGHT = 7,
	NONE = 0
};


class Players : public Entity {
public:
	static const int WIDTH = 5;
	static const int HEIGHT = 6;
	static const int PlayersMaxBombe = 2;


	int BombePosingNumber = 0;
	Players* PlayersCible = nullptr;
	int IndexPlayers;
	Color colorPlayers;
	Image img;
	Bombe* bombeArray[PlayersMaxBombe] = { nullptr };
	int TimerToMove = Utils::RandomTimePnjAction();
	positionMove posArrayToMoveInSecurity[2];

	Players(int x, int y, TypeEntity typeEntity, int indexPlayers, Image image, const Color colorIA = WHITE) {
		_x = x;
		_y = y;
		_width = WIDTH;
		_height = HEIGHT;
		IndexPlayers = indexPlayers;
		_typeEntity = typeEntity;
		img = image;
		if (typeEntity == TypeEntity::Ia)
		{
			colorPlayers = colorIA;

		}
	}

	int getX() {
		return _x;
	}
	int getY() {
		return _y;
	}
	int getWidth() {
		return _width;
	}
	int getHeight() {
		return _height;
	}
	TypeEntity getType() {
		return getTypeEntity();
	}

	void Move(positionMove move) {
		switch (move)
		{
		case positionMove::DOWN:
			if (PlayersCanMove(DOWN)) {
				_y += DOWN;
			}
			break;
		case positionMove::LEFT:
			if (PlayersCanMove(LEFT)) {
				_x += LEFT;
			}
			break;
		case positionMove::RIGHT:
			if (PlayersCanMove(RIGHT)) {
				_x += RIGHT;
			}
			break;
		case positionMove::UP:
			if (PlayersCanMove(UP)) {
				_y += UP;
			}
			break;
		}
	}

	void getCible()
	{
		int cibleInt = IndexPlayers;
		while (cibleInt == IndexPlayers)
		{
			cibleInt = rand() % 3;
		}

		PlayersCible = (Players*)General::PlayersArrays[cibleInt];
	}

	void update() {

		gb.display.print(this->IndexPlayers);
		gb.display.print(".");
		gb.display.print(this->BombePosingNumber);
		gb.display.print("-");

		if (getTypeEntity() == TypeEntity::Ia)
		{
			gb.display.setColor(colorPlayers);
			gb.display.fillCircle(_x, _y, 2);
			DebugPnj();
			TimerToMove--;
			DeplacementPnj(this);
		}
		else
		{
			gb.display.drawImage(_x, _y+1, img);
		}

		int cpt = 0;


		// Actualisation des bombes
		for (Bombe* bombe : bombeArray)
		{
			if (bombe == nullptr) {
				continue;
			}

			if (bombe->TimerBombe <= 0)
			{
				/*General::EntityArray[bombe->_indexBombe] = nullptr;*/
				bombeArray[cpt] = nullptr;
				this->BombePosingNumber--;
				if (BombePosingNumber <= 0) {
					BombePosingNumber = 0;
				}
			}
			cpt++;
		}

	}
	/// <summary>
	/// Affiche un cercle sur la cible du joueur qui le prends en chasse
	/// </summary>
	void DebugPnj() {
		gb.display.drawCircle(PlayersCible->getX(), PlayersCible->getY(), 5);
		//gb.display.print(IndexPlayers);
		//gb.display.print(".");
		//gb.display.print(PlayersCible->IndexPlayers);
		//gb.display.print("-");
	}

	bool PlayersCanMove(positionMove moveTO) {
		bool tmp = true;

		if (moveTO == positionMove::LEFT || moveTO == positionMove::RIGHT)
		{
			// si on sort de l'écran
			if (this->getX() + moveTO <= 0 || this->getX() + moveTO >= 77) {
				return false;
			}
			gb.display.setCursor(0, 0);
			gb.display.setColor(YELLOW);

			// si la position du joueur + ou - X entre en collision avec une entity alors il ne bouge pas
			for (Entity* entity : General::EntityArray) {

				if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), this->getX() + moveTO, this->getY(), this->getWidth(), this->getHeight())) {
					tmp = false;
				}
			}

		}
		else {

			if (this->getY() + moveTO < 7 || this->getY() + moveTO >= 63) {
				return false;
			}

			// si la position du joueur + ou - Y entre en collision avec une entity alors il ne bouge pas
			for (Entity* entity : General::EntityArray) {
				if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), this->getX(), this->getY() + moveTO, this->getWidth(), this->getHeight())) {
					tmp = false;
				}
			}
		}

		return tmp;
	}

	positionMove* PnjCanMoveInSecurity()
	{

		positionMove positionArray[4] = { UP,DOWN,LEFT,RIGHT };
		positionMove posOne = NONE;
		positionMove posTwo = NONE;
		positionMove lastPos = NONE;

		for (positionMove pos : positionArray)
		{
			posOne = NONE;
			posTwo = NONE;
			lastPos = NONE;
			int NewPosX;
			int NewPosY;
			if (pos == UP || pos == DOWN) {
				NewPosY = this->getY() + pos;
				NewPosX = this->getX();

				if (NewPosY< General::PositionZero || NewPosY> General::ScreenHeight)
				{
					continue;
				}
			}
			else {
				NewPosY = this->getY();
				NewPosX = this->getX() + pos;
				if (NewPosX< General::PositionZero || NewPosX> General::ScreenWidth)
				{
					continue;
				}
			}

			bool hasRencontreEntityInPerimeter = false;

			// si la position du joueur + ou - X entre en collision avec une entity 
			for (Entity* entity : General::EntityArray) {

				if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), NewPosX, NewPosY, this->getWidth(), this->getHeight())) {
					// si je rencontre quelque choses
					hasRencontreEntityInPerimeter = true;
				}
			}

			for (Entity* player : General::PlayersArrays) {
				if (gb.collide.rectRect(player->getX(), player->getY(), player->getWidth(), player->getHeight(), NewPosX, NewPosY, this->getWidth(), this->getHeight())) {
					hasRencontreEntityInPerimeter = true;
				}
			}


			if (hasRencontreEntityInPerimeter)
			{
				continue;
			}

			// si j'ai rien rencontrer dans le périmètre
			posArrayToMoveInSecurity[0] = pos;
			lastPos = GetLastPos(posOne);

			// je regarde dans le périmètre de la futur position :
			for (positionMove posPlus : positionArray)
			{
				// je ne prends pas en compte la position d'où je viens:
				if (posPlus == lastPos) {
					continue;
				}
				int NewPosXPlus;
				int NewPosYPlus;
				if (posPlus == UP || posPlus == DOWN) {
					NewPosYPlus = NewPosY + posPlus;
					NewPosXPlus = NewPosX;
				}
				else {
					NewPosYPlus = NewPosY;
					NewPosXPlus = NewPosX + posPlus;
				}
				// si la position du joueur + ou - X entre en collision avec une entity 
				for (Entity* entity : General::EntityArray) {

					if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), NewPosXPlus, NewPosYPlus, this->getWidth(), this->getHeight())) {
						// si je rencontre quelque choses
						hasRencontreEntityInPerimeter = true;
					}
				}

				for (Entity* player : General::PlayersArrays)
				{
					if (gb.collide.rectRect(player->getX(), player->getY(), player->getWidth(), player->getHeight(), NewPosXPlus, NewPosYPlus, this->getWidth(), this->getHeight())) {
						hasRencontreEntityInPerimeter = true;
					}

				}

				if (hasRencontreEntityInPerimeter)
				{
					continue;
				}
				posArrayToMoveInSecurity[1] = posPlus;
				posTwo = posPlus;
				if (posOne != positionMove::NONE && posTwo != positionMove::NONE)
				{
					positionMove tmp[2] = { posOne ,posTwo };
					return tmp;
				}
			}

		}


	}

	positionMove GetLastPos(positionMove pos)
	{
		switch (pos)
		{
		case UP:
			return DOWN;
			break;
		case DOWN:
			return UP;
			break;
		case LEFT:
			return RIGHT;
			break;
		case RIGHT:
			return LEFT;
			break;
		case NONE:
			return NONE;
			break;
		default:
			break;
		}
	}

	void DeplacementPnj(Players* player) {
		if (TimerToMove > 0) {
			return;
		}


		TimerToMove = Utils::RandomTimePnjAction();

		/*======================== GESTION DEPLACEMENT HAUT BAS =======================*/
			//  pnj va en haut sinon il va en bas
		if (this->PlayersCible->getY() < _y) {
			TypeEntity typeEntite = GetTypeEntityAround(UP);

			if (typeEntite == emptyCase)
			{
				Move(UP);
			}

			if (typeEntite == TypeEntity::briquesDestructible || typeEntite == TypeEntity::players || typeEntite == TypeEntity::Ia)
			{
				positionMove* pos = PnjCanMoveInSecurity();
				if (posArrayToMoveInSecurity[0] == positionMove::NONE || posArrayToMoveInSecurity[1] == positionMove::NONE)
				{

				}
				else {
					PoseBombe();
					Move(posArrayToMoveInSecurity[0]);
					Move(posArrayToMoveInSecurity[1]);
				}
			}
		}
		else {
			TypeEntity typeEntite = GetTypeEntityAround(DOWN);
			if (typeEntite == emptyCase)
			{
				Move(DOWN);
			}
			if (typeEntite == TypeEntity::briquesDestructible || typeEntite == TypeEntity::players || typeEntite == TypeEntity::Ia) {
				positionMove* pos = PnjCanMoveInSecurity();
				if (posArrayToMoveInSecurity[0] == positionMove::NONE || posArrayToMoveInSecurity[1] == positionMove::NONE)
				{

				}
				else {
					PoseBombe();
					Move(posArrayToMoveInSecurity[0]);
					Move(posArrayToMoveInSecurity[1]);
				}
			}

		}

		/*======================== GESTION DEPLACEMENT COTÉ =======================*/
		// si le x du joueur cible est plus petit que moi 
		// je vais a gauche sinon a droite

			// si pas d'obstacle avance 
			// si rencontre un bloc pose une bombe. 
		if (this->PlayersCible->getX() < _x) {
			TypeEntity typeEntite = GetTypeEntityAround(LEFT);
			if (typeEntite == emptyCase)
			{
				Move(LEFT);
			}
			// s'il a une brique un joueur ou une ia il pose une bombe et s'écarte
			if (typeEntite == TypeEntity::briquesDestructible || typeEntite == TypeEntity::players || typeEntite == TypeEntity::Ia) {
				positionMove* pos = PnjCanMoveInSecurity();
				if (posArrayToMoveInSecurity[0] == positionMove::NONE || posArrayToMoveInSecurity[1] == positionMove::NONE)
				{

				}
				else {
					PoseBombe();
					Move(posArrayToMoveInSecurity[0]);
					Move(posArrayToMoveInSecurity[1]);
				}
			}
		}
		else {
			TypeEntity typeEntite = GetTypeEntityAround(RIGHT);
			if (typeEntite == emptyCase)
			{
				Move(RIGHT);
			}
			if (typeEntite == TypeEntity::briquesDestructible || typeEntite == TypeEntity::players || typeEntite == TypeEntity::Ia) {
				positionMove* pos = PnjCanMoveInSecurity();
				if (posArrayToMoveInSecurity[0] == positionMove::NONE || posArrayToMoveInSecurity[1] == positionMove::NONE)
				{
					
				}
				else {
					PoseBombe();
					Move(posArrayToMoveInSecurity[0]);
					Move(posArrayToMoveInSecurity[1]);
				}
			}
		}
		posArrayToMoveInSecurity[0] = positionMove::NONE;
		posArrayToMoveInSecurity[1] = positionMove::NONE;
	}

	TypeEntity GetTypeEntityAround(positionMove moveTO)
	{
		if (moveTO == positionMove::LEFT || moveTO == positionMove::RIGHT)
		{
			// si la position du joueur + ou - X entre en collision avec une entity 
			for (Entity* entity : General::EntityArray) {

				if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), this->getX() + moveTO, this->getY(), this->getWidth(), this->getHeight())) {
					return entity->getTypeEntity();
				}
			}

			for (Entity* player : General::PlayersArrays) {
				if (gb.collide.rectRect(player->getX(), player->getY(), player->getWidth(), player->getHeight(), this->getX() + moveTO, this->getY(), this->getWidth(), this->getHeight())) {
					return player->getTypeEntity();
				}
			}
		}
		else { // regarde en haut ou en bas
			for (Entity* entity : General::EntityArray) {
				if (gb.collide.rectRect(entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight(), this->getX(), this->getY() + moveTO, this->getWidth(), this->getHeight())) {
					return entity->getTypeEntity();
				}
			}

			for (Entity* player : General::PlayersArrays) {
				if (gb.collide.rectRect(player->getX(), player->getY(), player->getWidth(), player->getHeight(), this->getX(), this->getY() + moveTO, this->getWidth(), this->getHeight())) {
					return player->getTypeEntity();
				}
			}
		}

		return TypeEntity::emptyCase;
	}

	void PoseBombe() {
		if (this->BombePosingNumber == Players::PlayersMaxBombe) {
			return;
		}
		this->BombePosingNumber++;
		Bombe* bombe = new Bombe(this->getX(), this->getY(), General::CompteurEntite);
		bombeArray[BombePosingNumber] = bombe;

		General::EntityArray[General::CompteurEntite] = bombe;

		General::CompteurEntite++;

		if (General::CompteurEntite >= General::maxEntite)
		{
			General::CompteurEntite = 100; // on efface pas les 100 premièere entite ( les briques etc...)
		}

	}
};


#endif

