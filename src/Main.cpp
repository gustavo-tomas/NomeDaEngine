#include "../header/Game.h"
#include "../header/TitleState.h"

int main(int argc, char** argv)
{
    Game& game = Game::GetInstance();
    game.Push(new TitleState());
    game.Run();
    return 0;
}

// @TODO: refactor Resources!
// @TODO: fix text offset on title screen
// @TODO: fix sound on end screen
