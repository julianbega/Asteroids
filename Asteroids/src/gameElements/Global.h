	#ifndef GLOBAL_H
#define GLOBAL_H

#include "raylib.h"
#include <math.h>
namespace AsteroidsJ
{
	
	enum GameStage
	{
		MENU, GAME, CREDITS, EXIT
	};
	extern GameStage gamestatus;

	
	static bool gameOver = false;
	static bool pause = false;
	static bool victory = false;

	const int screenWidth = 800;
	const int screenHeight = 450;

}
#endif

