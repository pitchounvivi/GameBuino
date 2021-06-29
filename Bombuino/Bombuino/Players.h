

#ifndef _Players_h
#define _Players_h
#pragma once

#include <Gamebuino-Meta.h>
#include "Utils.h"
#include "General.h"
#include "Entity.h"
#include "Bombe.h"
#include "MOVES.h"


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Players : public Entity {
public:
	static const int WIDTH = 5;
	static const int HEIGHT = 6;
	static const int PlayersMaxBombe = 2;


	int BombePosingNumber = 0;
	int IndexPlayers;
	Color colorPlayers;
	Image img;
	Bombe* bombeArray[PlayersMaxBombe] = { nullptr };
	int TimerToMove = Utils::RandomTimePnjAction();
	MOVES posArrayToMoveInSecurity[2];

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

	void Move(MOVES move) {
		switch (move)
		{
		case MOVES::DOWN:
			if (PlayersCanMove(DOWN)) {
				_y += DOWN;
			}
			break;
		case MOVES::LEFT:
			if (PlayersCanMove(LEFT)) {
				_x += LEFT;
			}
			break;
		case MOVES::RIGHT:
			if (PlayersCanMove(RIGHT)) {
				_x += RIGHT;
			}
			break;
		case MOVES::UP:
			if (PlayersCanMove(UP)) {
				_y += UP;
			}
			break;
		}
	}


	void update() {

		//gb.display.print(this->IndexPlayers);
		//gb.display.print(".");
		//gb.display.print(this->BombePosingNumber);
		//gb.display.print("-");

		if (getTypeEntity() == TypeEntity::Ia)
		{
			gb.display.setColor(colorPlayers);
			gb.display.fillCircle(_x+3, _y+3, 2);
			TimerToMove--;
			DeplacementPnj();
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

	bool PlayersCanMove(MOVES moveTO) {
		bool tmp = true;

		if (moveTO == MOVES::LEFT || moveTO == MOVES::RIGHT)
		{
			// si on sort de l'écran
			if (this->getX() + moveTO <= 0 || this->getX() + moveTO >= 77) {
				return false;
			}
			gb.display.setCursor(0, 0);
			gb.display.setColor(YELLOW);

			// si la position du joueur + ou - X entre en collision avec une entity alors il ne bouge pas
			const Node<Entity>* iterator = General::entities.get_head();

			while (iterator) {

				if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), this->getX() + moveTO, this->getY(), this->getWidth(), this->getHeight())) {
					tmp = false;
				}
				iterator = iterator->_next;
			}

		}
		else {

			if (this->getY() + moveTO < 7 || this->getY() + moveTO >= 63) {
				return false;
			}

			// si la position du joueur + ou - Y entre en collision avec une entity alors il ne bouge pas
			const Node<Entity>* iterator = General::entities.get_head();

			while (iterator) {
				if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), this->getX(), this->getY() + moveTO, this->getWidth(), this->getHeight())) {
					tmp = false;
				}
				iterator = iterator->_next;

			}
		}

		return tmp;
	}

	void PnjCanMoveInSecurity()
	{

		MOVES positionArray[4] = { UP,DOWN,LEFT,RIGHT };
		MOVES posOne = NONE;
		MOVES posTwo = NONE;
		MOVES lastPos = NONE;

		for (MOVES pos : positionArray)
		{
			lastPos = NONE;
			int NewPosX;
			int NewPosY;
			if (pos == UP || pos == DOWN) {
				NewPosY = this->getY() + pos;
				NewPosX = this->getX();
				if (NewPosY< General::HEIGHT_CADRE_SCORE || NewPosY> General::ScreenHeight)
				{
					continue;
				}
			}
			else {
				NewPosY = this->getY();
				NewPosX = this->getX() + pos;
				if (NewPosX< General::POSITION_START_DRAW_X || NewPosX> General::POSITION_END_DRAW_X)
				{
					continue;
				}
			}

			bool hasRencontreEntityInPerimeter = false;

			// si la position du joueur + ou - X entre en collision avec une entity
			const Node<Entity>* iterator = General::entities.get_head();

			while (iterator) {

				if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), NewPosX, NewPosY, this->getWidth(), this->getHeight())) {
					// si je rencontre quelque choses
					hasRencontreEntityInPerimeter = true;
				}
				iterator = iterator->_next;
			}
			
			const Node<Entity>* iteratorP = (Node<Entity> *)General::players.get_head();

			while (iteratorP) {
				if (gb.collide.rectRect(iteratorP->_current->getX(), iteratorP->_current->getY(), iteratorP->_current->getWidth(), iteratorP->_current->getHeight(), NewPosX, NewPosY, this->getWidth(), this->getHeight())) {
					hasRencontreEntityInPerimeter = true;
				}
				iteratorP = iteratorP->_next;
			}


			if (hasRencontreEntityInPerimeter)
			{
				continue;
			}

			// si j'ai rien rencontrer dans le périmètre
			posArrayToMoveInSecurity[0] = pos;
			lastPos = GetLastPos(posArrayToMoveInSecurity[0]);

			// je regarde dans le périmètre de la futur position :
			for (MOVES posPlus : positionArray)
			{
				int NewPosXPlus;
				int NewPosYPlus;

				// je ne prends pas en compte la position d'où je viens:
				if (posPlus == lastPos) {
					continue;
				}



				if (posPlus == UP || posPlus == DOWN) {
					NewPosYPlus = NewPosY + posPlus;
					NewPosXPlus = NewPosX;

					if (NewPosYPlus< General::HEIGHT_CADRE_SCORE || NewPosYPlus> General::ScreenHeight)
					{
						continue;
					}
				}

				else {
					NewPosYPlus = NewPosY;
					NewPosXPlus = NewPosX + posPlus;
					if (NewPosXPlus< General::POSITION_START_DRAW_X || NewPosXPlus> General::POSITION_END_DRAW_X)
					{
						continue;
					}
				}

				// si la position du joueur + ou - X entre en collision avec une entity
				const Node<Entity>* iterator = General::entities.get_head();

				while (iterator) {

					if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), NewPosXPlus, NewPosYPlus, this->getWidth(), this->getHeight())) {
						// si je rencontre quelque choses
						hasRencontreEntityInPerimeter = true;
					}
					iterator = iterator->_next;
				}
				Node<Entity>* iteratorP = (Node<Entity>*)General::players.get_head();
				while (iteratorP)
				{
					if (gb.collide.rectRect(iteratorP->_current->getX(), iteratorP->_current->getY(), iteratorP->_current->getWidth(), iteratorP->_current->getHeight(), NewPosXPlus, NewPosYPlus, this->getWidth(), this->getHeight())) {
						if (iteratorP->_current == this)
						{
							continue;
						}
						hasRencontreEntityInPerimeter = true;
					}
					iteratorP = iteratorP->_next;
				}

				if (hasRencontreEntityInPerimeter)
				{
					continue;
				}
				posArrayToMoveInSecurity[1] = posPlus;
			}

		}


	}

	/// <summary>
	/// Retourne la derrnière position du joueur.
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	MOVES GetLastPos(MOVES pos)
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

	void DeplacementPnj() {
		if (TimerToMove > 0) {
			return;
		}
		TimerToMove = Utils::RandomTimePnjAction();

		posArrayToMoveInSecurity[0] = MOVES::NONE;
		posArrayToMoveInSecurity[1] = MOVES::NONE;

		// je regarde ce qu'il y a sur la case courante:
		TypeEntity typeEntiteInCurrentCase = GetEntityInCurrentCase();

		if (typeEntiteInCurrentCase == TypeEntity::bombes)
		{
			PnjCanMoveInSecurity();
			Move(posArrayToMoveInSecurity[0]);
			Move(posArrayToMoveInSecurity[1]);
			return;
		}

		if (this->BombePosingNumber != 0) {
			return;
		}

		MOVES pmvTmp = GetEmptyCaseBetweenIa();

		if (pmvTmp != NONE) 
		{
			Move(pmvTmp);
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

	bool Action(MOVES pos)
	{
		TypeEntity typeEntite = GetTypeEntityAround(pos);

		// s'il a une brique un joueur ou une ia il pose une bombe et s'écarte
		if (typeEntite == TypeEntity::briquesDestructible || typeEntite == TypeEntity::players || typeEntite == TypeEntity::Ia) {
			PnjCanMoveInSecurity();
			if (posArrayToMoveInSecurity[0] == MOVES::NONE || posArrayToMoveInSecurity[1] == MOVES::NONE)
			{
				//General::generalTexte = "ACTION none:";
				//General::generalInt = posArrayToMoveInSecurity[0];
				//General::generalInt2 = posArrayToMoveInSecurity[1];
				//General::Pause = true;
			}
			else {
				PoseBombe();
				General::generalTexte = "pOSE BOMBE Y:";
				General::generalInt = posArrayToMoveInSecurity[0];
				General::generalInt2 = posArrayToMoveInSecurity[1];
				General::Pause = true;
				Move(posArrayToMoveInSecurity[0]);
				Move(posArrayToMoveInSecurity[1]);
				return true;
			}
		}
		return false;
	}

	TypeEntity GetTypeEntityAround(MOVES moveTO)
	{
		if (moveTO == MOVES::LEFT || moveTO == MOVES::RIGHT)
		{
			// si la position du joueur + ou - X entre en collision avec une entity
			const Node<Entity>* iterator = General::entities.get_head();
			while (iterator) {

				if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), this->getX() + moveTO, this->getY(), this->getWidth(), this->getHeight())) {
					return iterator->_current->getTypeEntity();
				}
				iterator = iterator->_next;
			}

			Node<Entity>* iteratorP = (Node<Entity>*)General::players.get_head();
			while (iteratorP) {
				if (gb.collide.rectRect(iteratorP->_current->getX(), iteratorP->_current->getY(), iteratorP->_current->getWidth(), iteratorP->_current->getHeight(), this->getX() + moveTO, this->getY(), this->getWidth(), this->getHeight())) {
					return iteratorP->_current->getTypeEntity();
				}
				iteratorP = iteratorP->_next;
			}
		}
		else { // regarde en haut ou en bas
			const Node<Entity>* iterator = General::entities.get_head();

			while (iterator) {
				if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), this->getX(), this->getY() + moveTO, this->getWidth(), this->getHeight())) {
					return iterator->_current->getTypeEntity();
				}
				iterator = iterator->_next;
			}

			Node<Entity>* iteratorP = (Node<Entity>*)General::players.get_head();
			while (iteratorP) {
				if (gb.collide.rectRect(iteratorP->_current->getX(), iteratorP->_current->getY(), iteratorP->_current->getWidth(), iteratorP->_current->getHeight(), this->getX(), this->getY() + moveTO, this->getWidth(), this->getHeight())) {
					return iteratorP->_current->getTypeEntity();
				}
				iteratorP = iteratorP->_next;
			}
		}

		return TypeEntity::emptyCase;
	}

	TypeEntity GetEntityInCurrentCase() 
	{
		// si la position du joueur + ou - X entre en collision avec une entity
		const Node<Entity>* iterator = General::entities.get_head();

		while (iterator) {

			if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), this->getX(), this->getY(), this->getWidth(), this->getHeight())) {
				return iterator->_current->getTypeEntity();
			}
			iterator = iterator->_next;
		}

		Node<Entity>* iteratorP = (Node<Entity>*)General::players.get_head();
		while (iteratorP) {
			if (gb.collide.rectRect(iteratorP->_current->getX(), iteratorP->_current->getY(), iteratorP->_current->getWidth(), iteratorP->_current->getHeight(), this->getX(), this->getY(), this->getWidth(), this->getHeight())) {
				return iteratorP->_current->getTypeEntity();
			}
			iteratorP = iteratorP->_next;
		}
	}
	
	MOVES GetEmptyCaseBetweenIa() {
		MOVES positionArray[4] = { UP,DOWN,LEFT,RIGHT };
		MOVES EmptyCaseArray[4]{};

		int cptEmpty = 0;
		for (MOVES pos : positionArray)
		{
			int NewPosX;
			int NewPosY;
			if (pos == UP || pos == DOWN) {
				NewPosY = this->getY() + pos;
				NewPosX = this->getX();

				if (NewPosY< General::HEIGHT_CADRE_SCORE || NewPosY> General::ScreenHeight)
				{
					continue;
				}
			}
			else {
				NewPosY = this->getY();
				NewPosX = this->getX() + pos;
				if (NewPosX< General::POSITION_START_DRAW_X || NewPosX> General::POSITION_END_DRAW_X)
				{
					continue;
				}
			}

			bool hasRencontreEntityInPerimeter = false;

			// si la position du joueur + ou - X entre en collision avec une entity
			const Node<Entity>* iterator = General::entities.get_head();

			while (iterator) {

				if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), NewPosX, NewPosY, this->getWidth(), this->getHeight())) {
					// si je rencontre quelque choses
					hasRencontreEntityInPerimeter = true;
				}
				iterator = iterator->_next;
			}
			Node<Entity>* iteratorP = (Node<Entity>*)General::players.get_head();
			while (iteratorP) {
				if (gb.collide.rectRect(iteratorP->_current->getX(), iteratorP->_current->getY(), iteratorP->_current->getWidth(), iteratorP->_current->getHeight(), NewPosX, NewPosY, this->getWidth(), this->getHeight())) {
					hasRencontreEntityInPerimeter = true;
				}
				iteratorP = iteratorP->_next;
			}

			// si on a uen collision avec l'ia sur la case rechercher
			// on ne l'ajoute pas à au tableau
			if (hasRencontreEntityInPerimeter)
			{
				continue;
			}
			else 
			{
				EmptyCaseArray[cptEmpty] = pos;
				cptEmpty++;
			}
		}

		// on récupère une position random ou bouge le joueur en fonction du nombree d'empty case trouvé:

		gb.display.print(cptEmpty);
		if (cptEmpty == 0) 
		{
			return MOVES::NONE;
		}

		int random = rand() % cptEmpty;

		return EmptyCaseArray[random];
	}

	void PoseBombe() {
		if (this->BombePosingNumber == Players::PlayersMaxBombe) {
			return;
		}
		this->BombePosingNumber++;
		Bombe* bombe = new Bombe(this->getX(), this->getY());
		bombeArray[BombePosingNumber] = bombe;
		General::entities.push(bombe);
	}
};


#endif

