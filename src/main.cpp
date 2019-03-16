#include <time.h>
#include "Game.h"

int main()
{
    srand(time(NULL));
    Game game;

    game.init();
    game.run();


    return 0;
}
