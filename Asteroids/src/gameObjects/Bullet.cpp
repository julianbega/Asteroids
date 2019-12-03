#include "Bullet.h"
#include <math.h>
#include "raylib.h"
#include "game/Asteroids.h"
namespace AsteroidsJ
{
	Bullet::Bullet()
	{
		Init();
	}

	Bullet::~Bullet()
	{

	}

	void Bullet::Init()
	{
		position = { 0, 0 };
		speed = { 0, 0 };
		radius = 2;
		active = false;
		lifeSpawn = 0;
		color = WHITE;

	}

	void Bullet::Update()
	{
		if (position.x > screenWidth / 2 - 150 && position.x < screenWidth / 2 + 150) position.x = GetRandomValue(0, screenWidth);
		if (position.y > screenHeight / 2 - 150 && position.y < screenHeight / 2 + 150)  position.y = GetRandomValue(0, screenHeight);
		position = { position.x, position.y };

	}

	void Bullet::Draw()
	{
		if (active) DrawCircleV(position, radius, BLACK);
	}


}