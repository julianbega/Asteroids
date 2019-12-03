#include "MediumMeteor.h"
#include <math.h>
#include "raylib.h"
#include "game/Asteroids.h"
#include "gameElements/Game.h"
namespace AsteroidsJ
{
	MediumMeteor::MediumMeteor()
	{
		position = { -100, -100 };
		speed = { 0, 0 };
		radius = 20;
		active = false;
		color = BLUE;
	}

	MediumMeteor::~MediumMeteor()
	{

	}

	

	void MediumMeteor::Init()
	{
		
	}



	void MediumMeteor::Update()
	{
	}

	void MediumMeteor::Draw()
	{
		if (active) DrawCircleV(position, radius, GRAY);
		else DrawCircleV(position, radius, Fade(LIGHTGRAY, 0.3f));
	}


}