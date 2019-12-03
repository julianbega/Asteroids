#include "Meteor.h"
#include <math.h>
#include "raylib.h"
#include "game/Asteroids.h"
#include "gameElements/Game.h"
namespace AsteroidsJ
{
	Meteor::Meteor()
	{
		
	}

	Meteor::~Meteor()
	{

	}

	void Meteor::Init()
	{
		position = { 0.0f,0.0f };
		speed = { 0.0f,0.0f };
		radius = 40;
		active = true;
		color = BLUE;
		correctRange = false;
		posx, posy;
		velx, vely;

		
	}




	void Meteor::Update()
	{
		correctRange = false;
		posx = GetRandomValue(0, screenWidth);

		while (!correctRange)
		{
			if (posx > screenWidth / 2 - 150 && posx < screenWidth / 2 + 150) posx = GetRandomValue(0, screenWidth);
			else correctRange = true;
		}

		correctRange = false;

		posy = GetRandomValue(0, screenHeight);

		while (!correctRange)
		{
			if (posy > screenHeight / 2 - 150 && posy < screenHeight / 2 + 150)  posy = GetRandomValue(0, screenHeight);
			else correctRange = true;
		}

		position = { static_cast<float>(posx), static_cast<float>(posy) };

		correctRange = false;
		velx = GetRandomValue(-MeteorsSpeed, MeteorsSpeed);
		vely = GetRandomValue(-MeteorsSpeed, MeteorsSpeed);

		while (!correctRange)
		{
			if (velx == 0 && vely == 0)
			{
				velx = GetRandomValue(-MeteorsSpeed, MeteorsSpeed);
				vely = GetRandomValue(-MeteorsSpeed, MeteorsSpeed);
			}
			else correctRange = true;
		}
		speed = { static_cast<float>(velx), static_cast<float>(vely) };

	}

	void Meteor::Draw()
	{
		if (active) DrawCircleV(position, radius, DARKGRAY);
		else DrawCircleV(position, radius, Fade(LIGHTGRAY, 0.3f));
	}


}