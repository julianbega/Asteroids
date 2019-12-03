#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "gameElements/Global.h"
#include "Shoot.h"
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
		const float PlayerBaseSize = 20.0f;
		const float PlayerSpeed = 6.0f;
		const int PlayerMaxShoots = 10;
		Shoot *shoot[PLAYER_MAX_SHOOTS];
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