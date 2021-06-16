#include <Gamebuino-Meta.h>
#include <cstdlib>

void setup()
{
    gb.begin();
};

void loop()
{
    while (!gb.update());
    gb.display.clear();
}