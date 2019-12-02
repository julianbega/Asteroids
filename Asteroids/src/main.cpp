#include "Game.h"
using namespace AsteroidsJ;
int main()
{
	Game* game = new Game();
	game->Play();
	if (game) delete game;
	return 0;
}