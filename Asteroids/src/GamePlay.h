#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "Player.h"
namespace AsteroidsJ
{
	class GamePlay
	{
	public:
		GamePlay();
		~GamePlay();
		void Init();
		bool Update();
		void Draw();
		Music gameplayMusic;
	private:
		Player* player;
		Music gameMusic;
		Sound resetSong;
	};
}
#endif