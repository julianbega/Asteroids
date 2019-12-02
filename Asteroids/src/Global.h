#ifndef GLOBAL_H
#define GLOBAL_H

#include "raylib.h"
namespace AsteroidsJ
{
	enum GameStage
	{
		MENU, GAME, CREDITS, EXIT
	};
	extern GameStage gamestatus;


}
#endif
