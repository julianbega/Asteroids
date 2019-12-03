#include "game/Asteroids.h"
using namespace AsteroidsJ;
int main()
{
	Asteroids* game = new Asteroids();
	game->Play();
	if(game) delete game;
	return 0;
}