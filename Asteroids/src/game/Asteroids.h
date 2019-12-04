#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#include "raylib.h"
#include "gameElements/Game.h"
#include "gameElements/Menu.h"
#include "gameElements/Credits.h"
#include "gameElements/Global.h"
namespace AsteroidsJ
{
	class Asteroids
	{
	public:
		Asteroids();
		~Asteroids();
		void Play();

		Game* game;
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