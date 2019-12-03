#ifndef SMALLMETEOR_H
#define SMALLMETEOR_H

#include "raylib.h"
#include "gameElements/Global.h"
namespace AsteroidsJ
{
	class SmallMeteor
	{
	public:
		SmallMeteor();
		~SmallMeteor();
		void Init();
		void Update();
		void Draw();
		const int MeteorsSpeed = 2;
		Vector2 position;
		Vector2 speed;
		float radius;
		bool active;
		Color color;
		bool correctRange;
		int posx, posy;
		int velx, vely;
	private:

	};
}
#endif