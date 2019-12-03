#include "SmallMeteor.h"
#include <math.h>
#include "raylib.h"
#include "game/Asteroids.h"
#include "gameElements/Game.h"
namespace AsteroidsJ
{
	SmallMeteor::SmallMeteor()
	{
		position = { -100, -100 };
		speed = { 0, 0 };
		radius = 10;
		active = false;
		color = BLUE;
	}

	SmallMeteor::~SmallMeteor()
	{

	}


	void SmallMeteor::Init()
	{
		
	}

	void SmallMeteor::Update()
	{
	}

	void SmallMeteor::Draw()
	{
		if (active) DrawCircleV(position, radius, GRAY);
		else DrawCircleV(position, radius, Fade(LIGHTGRAY, 0.3f));
	}


}