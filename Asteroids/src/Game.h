#ifndef GAMES_H
#define GAMES_H
#include "raylib.h"

#include "GamePlay.h"
#include "Menu.h"
#include "Credits.h"
#include "Global.h"
namespace AsteroidsJ
{
	class Game
	{
	public:
		Game();
		~Game();
		void Play();
		const int screenWidth = 810;
		const int screenHeight = 450;

		GamePlay* gamePlay;
		Menu* menu;
		Credits* credits;
		bool firstTime;
	private:
		void Init();
		void Update();
		void Draw();
		bool inGame;
		Sound winSong;
	};
}
#endif