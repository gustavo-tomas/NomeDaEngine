#include "../header/Game.h"

int main(int argc, char** argv)
{
    Game::GetInstance().Run();
    return 0;
}

// Game::GetInstance().GetRenderer()