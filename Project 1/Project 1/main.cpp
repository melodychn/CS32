
#include "Game.h"

/////////////d//////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////
/*
int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}
*/
#include "History.h"
int main()
{
    History h(2, 2);
    h.record(1, 1);
    h.display();
}

