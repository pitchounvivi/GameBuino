// General.h



#ifndef _GENERAL_h
#define _GENERAL_h


#include "Entity.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class General
{
	public:
		static const int FPS;

		static int MyPlayerStartPositionX;
		static int MyPlayerStartPositionY;
		static int HeightCadreScore;
		static int PositionZero;
		static int PositionStartDrawX ;
		static int PositionEndDrawX ;
		static int BombeTimer;
		static int CompteurEntite;
		static int CompteurPlayers;
		static int ScreenWidth;
		static int ScreenHeight;

		const static int maxEntite = 300;
		static Entity* EntityArray[maxEntite];
		const static int NbPlayer = 3;

		static void InstanceUnbreakBrique();
		static void InstanceBreakeableBrique();
		static void DrawCadre();
		static void DrawBombe();
		static void DrawEntities();


	private:
		General() {}
};

#endif

