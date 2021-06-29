// 
// 
// 

#include "Utils.h"
#include <Gamebuino-Meta.h>



void Utils::DebugValueOnTopScreen(String texte, int value)
{
    gb.display.setCursorY(2);
    gb.display.setCursorX(2);
    gb.display.print(texte + ":");
    gb.display.print(value);
}

void Utils::DebugValueOnBottomScreen(String texte, int value)
{
    gb.display.setColor(WHITE);
    gb.display.setCursorY(58);
    gb.display.setCursorX(2);
    gb.display.print(texte + ":");
    gb.display.print(value);
}

int Utils::RandomInt() {
    return rand() % 3;

}


/// <summary>
/// Retourne le temps de r�action de l'IA 
/// Entre 0.75s et 2s
/// </summary>
/// <returns></returns>
int Utils::RandomTimePnjAction(){
    return rand() % 20 + 20; // si 0 +30 = 30 soit 0.75s de temps de r�ation / si 50 +30 = 80 soit 2s de temps de r�action
}

const uint16_t Utils::BOMB_TEXTURE[] = {
    // metadata

   7,      // frame width
   8,      // frame height
   3,      // frames
   22,      // frame loop
   0xf81f, // transparent color
   0,      // 16-bits color mode

   // colormap

   0xf81f, 0xf81f, 0xf81f, 0xa986, 0xf81f, 0xf81f, 0xf81f,
   0xf81f, 0xf81f, 0x6aeb, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
   0xf81f, 0x2106, 0x9492, 0x2106, 0xf81f, 0xf81f, 0xf81f,
   0x2106, 0x39cb, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
   0x2106, 0x39cb, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
   0x2106, 0x2927, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
   0xf81f, 0x18c5, 0x18c5, 0x18c5, 0xf81f, 0xf81f, 0xf81f,
   0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,

    0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
    0xf81f, 0xf81f, 0xa986, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
    0xf81f, 0x2106, 0x9492, 0x2106, 0xf81f, 0xf81f, 0xf81f,
    0x2106, 0x39cb, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
    0x2106, 0x39cb, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
    0x2106, 0x2927, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
    0xf81f, 0x18c5, 0x18c5, 0x18c5, 0xf81f, 0xf81f, 0xf81f,
    0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,

    0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
    0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
    0xf81f, 0x2106, 0xa986, 0x2106, 0xf81f, 0xf81f, 0xf81f,
    0x2106, 0x39cb, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
    0x2106, 0x39cb, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
    0x2106, 0x2927, 0x2927, 0x2927, 0x2106, 0xf81f, 0xf81f,
    0xf81f, 0x18c5, 0x18c5, 0x18c5, 0xf81f, 0xf81f, 0xf81f,
    0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f
};

const uint16_t Utils::BRIQUE_INCASSABLE[] = {
    // metadata

    7,      // frame width
    8,      // frame height
    1,      // frames
    0,      // frame loop
    0xf81f, // transparent color
    0,      // 16-bits color mode

    // colormap

    0x9a02, 0xfc08, 0xfc08, 0xfc08, 0xfc08, 0xfc08, 0x9a02,
    0xfc08, 0x9a02, 0xfc08, 0xfc08, 0xfc08, 0x9a02, 0xfc08,
    0xfc08, 0xfc08, 0x9a02, 0x9a02, 0x9a02, 0xfc08, 0xfc08,
    0xfc08, 0xfc08, 0x9a02, 0x9a02, 0x9a02, 0xfc08, 0xfc08,
    0xfc08, 0xfc08, 0x9a02, 0x9a02, 0x9a02, 0xfc08, 0xfc08,
    0xfc08, 0xfc08, 0x9a02, 0x9a02, 0x9a02, 0xfc08, 0xfc08,
    0xfc08, 0x9a02, 0xfc08, 0xfc08, 0xfc08, 0x9a02, 0xfc08,
    0x9a02, 0xfc08, 0xfc08, 0xfc08, 0xfc08, 0xfc08, 0x9a02

};

const uint16_t Utils::EXPLOSION_TEXTURE[] = {
    // metadata

     21,     // frame width
     24,     // frame height
     2,      // frames
     1,      // frame loop
     0xf81f, // transparent color
     0,      // 16-bits color mode

     // colormap

     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x9c7b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x9c7b, 0x7b94, 0x9cbb, 0xbc9e, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x6a3e, 0xbc9e, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x7a7e, 0x9c7b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x7a7e, 0x9c7b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x7a7e, 0xbc9e, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7b94, 0x5a1e, 0x7a7e, 0x9c7b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7394, 0x319d, 0x7a7e, 0x947b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x7b3e, 0x8c5b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0x6abb, 0x6abb, 0x6abb, 0x6abb, 0x6abb, 0x6abb, 0x6abb, 0x7abc, 0x9ade, 0xabbe, 0x8afd, 0x835c, 0x835c, 0x835c, 0x835c, 0x835c, 0x835c, 0x835c, 0x835c, 0xf81f,
     0x8c17, 0x6a5e, 0x8abe, 0xb43e, 0xbc7e, 0xbc9e, 0xce3f, 0xa39e, 0x9b3e, 0xcc9e, 0xd55f, 0xabde, 0x931e, 0xbc7e, 0x9b5e, 0x9b7e, 0x8abe, 0x8abe, 0x7a7e, 0x9c7b, 0x9c7b,
     0x8c1c, 0x829e, 0xa2fe, 0xccbe, 0xd51f, 0xe5bf, 0xf75f, 0xdddf, 0xcd9f, 0xee7f, 0xf6ff, 0xddff, 0xcd5e, 0xd4fe, 0xb3be, 0xb3de, 0xa2fe, 0x92be, 0x7a7e, 0x6a5d, 0x9c7b,
     0x943b, 0x9ade, 0x9ade, 0x9ade, 0xb3de, 0xdd5f, 0xdd5f, 0xf7bf, 0xf7bf, 0xffbf, 0xffbf, 0xf7bf, 0xf75f, 0xa33e, 0x9ade, 0x9ade, 0x9ade, 0x725e, 0x6a3e, 0x6a9c, 0x9c7b,
     0xf81f, 0x6a3e, 0x6a3e, 0x835c, 0x835c, 0x835c, 0x835c, 0x6a3e, 0x7a7e, 0xa2fe, 0xb3de, 0x8abe, 0x6a3e, 0x6a3e, 0x6a3e, 0x6a3e, 0x6a3e, 0x6a3e, 0x6a3e, 0x835c, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xa4fa, 0x727e, 0x9b9e, 0x7b19, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x7abe, 0x6b18, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x6a3e, 0x6318, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x7a7e, 0x7338, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x7a7e, 0x7338, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x9c7b, 0x6a3e, 0x7a7e, 0x7338, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x725e, 0x7338, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x9c7b, 0x941c, 0x72db, 0x7b95, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x9c7b, 0x9c7b, 0xbc9e, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x9c7b, 0xbc9e, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x6a3e, 0x6a3e, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x7a7e, 0x9c7b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x7a7e, 0x9c7b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x7a7e, 0xbc9e, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7b94, 0x5a1e, 0x7a7e, 0x9c7b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7394, 0x319d, 0x7a7e, 0x947b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7bb4, 0x6a3e, 0x7b3e, 0x8c5b, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0x6abb, 0x6abb, 0x6abb, 0x6abb, 0x6abb, 0x7abc, 0x9ade, 0xabbe, 0x8afd, 0x835c, 0x835c, 0x835c, 0x835c, 0x835c, 0x835c, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0x8abe, 0xb43e, 0xbc7e, 0xbc9e, 0xce3f, 0xa39e, 0x9b3e, 0xcc9e, 0xd55f, 0xabde, 0x931e, 0xbc7e, 0x9b5e, 0x9b7e, 0x8abe, 0x8abe, 0x835c, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xa2fe, 0xccbe, 0xd51f, 0xe5bf, 0xf75f, 0xdddf, 0xcd9f, 0xee7f, 0xf6ff, 0xddff, 0xcd5e, 0xd4fe, 0xb3be, 0xb3de, 0xa2fe, 0x92be, 0x7a7e, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0x9ade, 0xb3de, 0xdd5f, 0xdd5f, 0xf7bf, 0xf7bf, 0xffbf, 0xffbf, 0xf7bf, 0xf75f, 0xa33e, 0x9ade, 0x9afe, 0x9ade, 0x725e, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x7a7e, 0xa2fe, 0xb3de, 0x8abe, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xa4fa, 0x727e, 0x9b9e, 0x7319, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x7abe, 0x6b18, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x6a3e, 0x6318, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x7a7e, 0x7338, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x7a7e, 0x7338, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x9c7b, 0x6a3e, 0x7a7e, 0x7338, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xbc9e, 0x6a3e, 0x725e, 0x7338, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x941c, 0x72db, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
     0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f
};

const uint16_t Utils::ROBOT_TEXTURE[] = {
    // metadata

    5,      // frame width
    6,      // frame height
    1,      // frames
    0,      // frame loop
    0xf81f, // transparent color
    0,      // 16-bits color mode

    // colormap

    0xf81f, 0x69ec, 0x69ab, 0x69ab, 0xf81f,
    0x522e, 0x91ca, 0x522d, 0x9188, 0x498a,
    0xf81f, 0x41ac, 0x522d, 0x4169, 0xf81f,
    0x69ec, 0x4148, 0x4148, 0x4948, 0x61ab,
    0x71c9, 0x4948, 0x4929, 0x5148, 0x6969,
    0xf81f, 0x39ed, 0xf81f, 0x420d, 0xf81f
};

const uint16_t Utils::BRIQUE_DESTRUCTIBLE[] = {

    // metadata

    7,      // frame width
    8,      // frame height
    1,      // frames
    0,      // frame loop
    0xf81f, // transparent color
    0,      // 16-bits color mode

    // colormap

    0x39ee, 0x39ee, 0x39ee, 0x318b, 0x39ee, 0x39ee, 0x4a4c,
    0x31ab, 0x39ee, 0x39ee, 0x39ed, 0x39ee, 0x31ac, 0x526e,
    0x2969, 0x31ac, 0x31ac, 0x31ac, 0x31ab, 0x296a, 0x422c,
    0x2107, 0x2107, 0x2107, 0x2107, 0x2107, 0x2107, 0x2967,
    0x2107, 0x318b, 0x318a, 0x2948, 0x318b, 0x318b, 0x31aa,
    0x2107, 0x318b, 0x2949, 0x296a, 0x2969, 0x318b, 0x31aa,
    0x2107, 0x318b, 0x2969, 0x296a, 0x2969, 0x296a, 0x31aa,
    0x2107, 0x318b, 0x318a, 0x2948, 0x318a, 0x2948, 0x31aa

};