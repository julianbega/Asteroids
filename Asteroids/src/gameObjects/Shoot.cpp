#include "Shoot.h"
#include <math.h>
#include "raylib.h"
#include "game/Asteroids.h"
namespace AsteroidsJ
{
	Shoot::Shoot()
	{
		Init();
	}

	Shoot::~Shoot()
	{

	}

	void Shoot::Init()
	{
		position = { 0, 0 };
		speed = { 0, 0 };
		radius = 2;
		active = false;
		lifeSpawn = 0;
		color = WHITE;

	}

	void Shoot::Update()
	{
		if (position.x > screenWidth / 2 - 150 && position.x < screenWidth / 2 + 150) position.x = GetRandomValue(0, screenWidth);
		if (position.y > screenHeight / 2 - 150 && position.y < screenHeight / 2 + 150)  position.y = GetRandomValue(0, screenHeight);
		position = { position.x, position.y };

	}

	void Shoot::Draw()
	{
		if (active) DrawCircleV(position, radius, BLACK);
	}


}