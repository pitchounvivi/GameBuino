// General.h



#ifndef _GENERAL_h
#define _GENERAL_h


#include "Entity.h"
#include "Node.h"
#include "List.h"

// no circular dependency just metionning a players class
class Players;

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class General
{
	public:
		static const int FPS;

		static const int MY_PLAYER_START_POSITION_X;
		static const int MY_PLAYER_START_POSITION_Y;
		static const int HEIGHT_CADRE_SCORE;
		static const int POSITION_ZERO;
		static const int POSITION_START_DRAW_X;
		static const int POSITION_END_DRAW_X;
		static const int BOMBE_TIMER;
		static int CompteurPlayers;
		static const int ScreenWidth;
		static const int ScreenHeight;
		static char* generalTexte;
		static char* generalTexte2;		
		static int generalInt;
		static int generalInt2;
		static List<Entity> entities;
		static List<Players> players;
		const static int NB_PLAYER = 3;
		//static Entity* PlayersArrays[3];
		static void InstanceUnbreakBrique();
		static void InstanceBreakeableBrique();
		static void DrawCadre();
		static void DrawBombe();
		static void DrawEntities();

		static String MsgUp;
		static String MsgDown;

		static bool Pause;
	private:
		General() {}
};

#endif

