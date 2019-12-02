#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
namespace AsteroidsJ
{
	class Player
	{
	public:

		Player();
		~Player();
		void Init();
		void Update();
		void Draw();
	private:
		Vector2 position;
		Vector2 speed;
		float acceleration;
		float rotation;
		Vector3 collider;
		Color color;
	};
}
#endif