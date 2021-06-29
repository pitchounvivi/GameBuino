// Utils.h

#ifndef _UTILS_h
#define _UTILS_h
#include <Gamebuino-Meta.h>


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Utils
{
	public:
		static void DebugValueOnTopScreen(String texte, int value);
		static void DebugValueOnBottomScreen(String texte, int value);

		const static uint16_t BOMB_TEXTURE[];
		const static uint16_t EXPLOSION_TEXTURE[];
		const static uint16_t BRIQUE_INCASSABLE[];
		const static uint16_t ROBOT_TEXTURE[];
		const static uint16_t BRIQUE_DESTRUCTIBLE[];
		const static uint16_t ALIEN_TEXTURE[];
		const static uint16_t WOMAN_TEXTURE[];
		const static uint16_t DOG_TEXTURE[];

		static int RandomInt();
		static int RandomTimePnjAction();

	private:
		Utils() {}
};

#endif

