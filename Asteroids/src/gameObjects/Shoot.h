#ifndef SHOOT_H
#define SHOOT_H
#include "raylib.h"
#include "gameElements/Global.h"
namespace AsteroidsJ
{
	class Shoot
	{
	public:
		Shoot();
		~Shoot();
		void Init();
		void Update();
		void Draw();

		Vector2 position;
		Vector2 speed;
		float radius;
		float rotation;
		int lifeSpawn;
		bool active;
		Color color;
	private:

	};
}
#endif