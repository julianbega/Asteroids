#ifndef GLOBAL_H
#define GLOBAL_H

namespace AsteroidsJ
{
	
	enum GameStage
	{
		MENU, GAME, CREDITS, EXIT, END
	};
	extern GameStage gamestatus;

	
	static bool gameOver = false;
	static bool pause = false;
	static bool victory = false;

	const int screenWidth = 800;
	const int screenHeight = 450;
	const int tilescale = 30;
	const int TEXTDISTANCEINX = 2;
	const int PLAYTEXTDISTANCEINY = 6;
	const int CONTROLESTEXTDISTANCEINY = 8;
	const int CREDITSTEXTDISTANCEINY = 10;
	const int EXITTEXTDISTANCEINY = 12;
}
#endif

