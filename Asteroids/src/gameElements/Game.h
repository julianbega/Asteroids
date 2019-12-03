#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include <math.h>

#include "gameElements/Global.h"
#include "gameObjects/Player.h"
#include "gameObjects/Bullet.h"
#include "gameObjects/Meteor.h"
#include "gameObjects/MediumMeteor.h"
#include "gameObjects/SmallMeteor.h"
namespace AsteroidsJ
{
	const int MAX_BIG_METEORS = 4;
	const int MAX_MEDIUM_METEORS = 8;
	const int MAX_SMALL_METEORS = 16;

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
		Music gameMusic;
		Sound resetSong;
		Meteor* bigMeteor[MAX_BIG_METEORS];
		MediumMeteor* mediumMeteor[MAX_MEDIUM_METEORS];
		SmallMeteor* smallMeteor[MAX_SMALL_METEORS];
	private:

	};
	
	static int midMeteorsCount;
	static int smallMeteorsCount;
	static int destroyedMeteorsCount;
	static float shipHeight;


}
#endif