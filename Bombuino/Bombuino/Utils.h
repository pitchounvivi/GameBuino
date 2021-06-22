// Utils.h

#ifndef _UTILS_h
#define _UTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Utils
{
	public:
		static void DebugMessageOnTopScreen(String texte, int value);
		static void DebugMessageOnBottomScreen(String texte, int value);
		const static uint16_t BOMB_TEXTURE[];
		const static uint16_t EXPLOSION_TEXTURE[];
		const static uint16_t BRIQUE_INCASSABLE[];
		const static uint16_t ROBOT_TEXTURE[];

	private:
		Utils() {}
};

#endif

