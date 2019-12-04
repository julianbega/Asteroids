#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "gameElements/Global.h"
#include "gameObjects/Player.h"
namespace AsteroidsJ
{
	const int MAX_BIG_METEORS = 4;
	const int MAX_MEDIUM_METEORS = 8;
	const int MAX_SMALL_METEORS = 16;



	typedef struct Shoot {
		Vector2 position;
		Vector2 speed;
		float radius;
		float rotation;
		int lifeSpawn;
		bool active;
		Color color;
	} Shoot;

	typedef struct Rock {
		Vector2 position;
		Vector2 speed;
		float radius;
		bool active;
		Color color;
	} Rock;


	class Game
	{
	public:
		Game();
		~Game();
		void Init();
		bool Update();
		void Draw();	
		Music gameplayMusic;
		float volume;		
		Player* player;		
		const int MeteorsSpeed = 2;
		int midMeteorsCount;
		int smallMeteorsCount;
		int destroyedMeteorsCount;
		Rock bigMeteor[MAX_BIG_METEORS];
		Rock mediumMeteor[MAX_MEDIUM_METEORS];
		Rock smallMeteor[MAX_SMALL_METEORS];
		Shoot shoot[PLAYER_MAX_SHOOTS];		
	private:

		Sound AsteroidsBreack;
	};
	

}
#endif