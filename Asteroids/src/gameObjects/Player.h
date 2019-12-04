#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
namespace AsteroidsJ
{

	const int PLAYER_MAX_SHOOTS = 10;

	class Player
	{
	public:
		Player();
		~Player();
		void Input();
		void Init();
		void Update();
		void Draw();
		const float playerBaseSize = 20.0f;
		const float playerSpeed = 6.0f;
		const int playerMaxShoots = 10;
		int lives;
		Vector2 position;
		Vector2 speed;
		float acceleration;
		float rotation;
		Vector3 collider;
		Color color;
		float shipHeight;
		int destroyedMeteorsCount;
	private:
		
	};
}
#endif