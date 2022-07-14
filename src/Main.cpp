#include "../header/Game.h"
#include "../header/StageState.h"

int main(int argc, char** argv)
{
    Game& game = Game::GetInstance();
    game.Push(new StageState());
    game.Run();
    return 0;
}