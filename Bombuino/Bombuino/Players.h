

#ifndef _Players_h
#define _Players_h
#pragma once

#include <Gamebuino-Meta.h>
#include "Utils.h"
#include "General.h"
#include "Entity.h"
#include "MOVES.h"


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Bombe;
class Players : public Entity {
private:
	void controls();
	void controlsIA();
public:
	static const int WIDTH = 5;
	static const int HEIGHT = 6;
	static const int PlayersMaxBombe = 2;


	int BombePosingNumber = 0;
	Color colorPlayers;
	Image img;
	int timerNextMove = Utils::randomTimerNextAction();
	MOVES posArrayToMoveInSecurity[2];

	Players(int x, int y, TypeEntity typeEntity, Image image, const Color colorIA = WHITE);

	int getX() {
		return _x;
	}

	int getY() {
		return _y;
	}

	int getWidth() {
		return WIDTH;
	}

	int getHeight() {
		return HEIGHT;
	}

	TypeEntity getType() {
		return getTypeEntity();
	}

	void move(MOVES move) {
		if (playerCanMove(move)) {
			if (move == MOVES::DOWN || move == MOVES::UP) {
				_y += move;
			}
			if (move == MOVES::LEFT || move == MOVES::RIGHT) {
				_x += move;
			}
		}
	}

	void decBombCount();

	void update() {
		
		controls();
		controlsIA();

		int cpt = 0;
	}

	bool playerCanMove(MOVES moveTO) {
		const Node<Entity>* iterator = General::entities.get_head();
		while (iterator) {
			if ((moveTO == MOVES::LEFT || moveTO == MOVES::RIGHT) &&
				gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(),
					iterator->_current->getWidth(), iterator->_current->getHeight(),
					this->getX() + moveTO, this->getY(), this->getWidth(), this->getHeight())) {
				return false;
			}

			if ((moveTO == MOVES::UP || moveTO == MOVES::DOWN) && 
				gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(),
				iterator->_current->getWidth(), iterator->_current->getHeight(), this->getX(),
				this->getY() + moveTO, this->getWidth(), this->getHeight())) {
				return false;
			}
			iterator = iterator->_next;
		}
		return true;
	}

	// TODO use recursive func more readable
	void iaCalcSecurePlaces()
	{
		MOVES positionArray[4] = { UP,DOWN,LEFT,RIGHT };
		MOVES posOne = NONE;
		MOVES posTwo = NONE;
		MOVES lastPos = NONE;

		for (MOVES pos : positionArray) {
			lastPos = NONE;
			int NewPosX;
			int NewPosY;
			if (pos == UP || pos == DOWN) {
				NewPosY = this->getY() + pos;
				NewPosX = this->getX();
				if (NewPosY< General::HEIGHT_CADRE_SCORE || NewPosY> General::ScreenHeight) {
					continue;
				}
			} else {
				NewPosY = this->getY();
				NewPosX = this->getX() + pos;
				if (NewPosX< General::POSITION_START_DRAW_X || NewPosX> General::POSITION_END_DRAW_X) {
					continue;
				}
			}

			// si la position du joueur + ou - X entre en collision avec une entity
			const Node<Entity>* iterator = General::entities.get_head();
			while (iterator) {
				if (gb.collide.rectRect(iterator->_current->getX(), iterator->_current->getY(), iterator->_current->getWidth(), iterator->_current->getHeight(), NewPosX, NewPosY, this->getWidth(), this->getHeight())) {
					// si je rencontre quelque choses
					continue;
				}
				iterator = iterator->_next;
			}
			
			const Node<Entity>* iteratorP = (Node<Entity> *)General::players.get_head();
			while (iteratorP) {
				if (gb.collide.rectRect(iteratorP->_current->getX(), iteratorP->_current->getY(), iteratorP->_current->getWidth(), iteratorP->_current->getHeight(), NewPosX, NewPosY, this->getWidth(), this->getHeight())) {
					continue;
				}
				iteratorP = iteratorP->_next;
			}

			// si j'ai rien rencontrer dans le périmètre
			posArrayToMoveInSecurity[0] = pos;
			lastPos = getLastPosition(posArrayToMoveInSecurity[0]);

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
						continue;
					}
					iterator = iterator->_next;
				}
				Node<Entity>* iteratorP = (Node<Entity>*)General::players.get_head();
				while (iteratorP)
				{
					if (gb.collide.rectRect(iteratorP->_current->getX(), iteratorP->_current->getY(), iteratorP->_current->getWidth(), iteratorP->_current->getHeight(), NewPosXPlus, NewPosYPlus, this->getWidth(), this->getHeight())) {
						continue;
					}
					iteratorP = iteratorP->_next;
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
	MOVES getLastPosition(MOVES pos) {
		switch (pos) {
			case UP:
				return DOWN;
			case DOWN:
				return UP;
			case LEFT:
				return RIGHT;
			case RIGHT:
				return LEFT;
			case NONE:
				return NONE;
		}
	}

	bool Action(MOVES pos)
	{
		TypeEntity typeEntite = GetTypeEntityAround(pos);

		// s'il a une brique un joueur ou une ia il pose une bombe et s'écarte
		if (typeEntite == TypeEntity::BRIQUES_BREAK || typeEntite == TypeEntity::PLAYER || typeEntite == TypeEntity::IA) {
			iaCalcSecurePlaces();
			if (posArrayToMoveInSecurity[0] != MOVES::NONE && posArrayToMoveInSecurity[1] != MOVES::NONE) {
				PoseBombe();
				move(posArrayToMoveInSecurity[0]);
				move(posArrayToMoveInSecurity[1]);
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
		} else { // regarde en haut ou en bas
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

		return TypeEntity::EMPTY;
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

	void PoseBombe();
};


#endif

