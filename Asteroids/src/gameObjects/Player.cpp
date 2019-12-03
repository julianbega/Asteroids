#include "Player.h"
#include <math.h>
#include "raylib.h"
#include "game/Asteroids.h"
#include "gameElements/Global.h"
#include "Bullet.h"
namespace AsteroidsJ
{
	Player::Player()
	{
		Init();
	}

	Player::~Player()
	{

	}

	void Player::Input()
	{
		if (IsKeyDown(KEY_LEFT)) rotation -= 5;
		if (IsKeyDown(KEY_RIGHT)) rotation += 5;
		if (IsKeyDown(KEY_UP))
		{
			if (acceleration < 1) acceleration += 0.04f;
		}
		else
		{
			if (acceleration > 0) acceleration -= 0.02f;
			else if (acceleration < 0) acceleration = 0;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			if (acceleration > 0) acceleration -= 0.04f;
			else if (acceleration < 0) acceleration = 0;
		}
		if (IsKeyPressed(KEY_SPACE))
		{
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if (shoot[i] != NULL)
				{
					shoot[i]->Init();
					if (!shoot[i]->active)
					{
						shoot[i]->position = { position.x + static_cast<float>(sin(rotation*DEG2RAD))*(shipHeight), position.y - static_cast<float>(cos(rotation*DEG2RAD))*(shipHeight) };
						shoot[i]->active = true;
						shoot[i]->speed.x = 1.5*sin(rotation*DEG2RAD)*PlayerSpeed;
						shoot[i]->speed.y = 1.5*cos(rotation*DEG2RAD)*PlayerSpeed;
						shoot[i]->rotation = rotation;
						break;
					}
				}
			}
		}
	}

	void Player::Init()
	{
		position = { screenWidth / 2, screenHeight / 2 - shipHeight / 2 };
		speed = { 0, 0 };
		acceleration = 0;
		rotation = 0;
		collider = { position.x + static_cast<int>(sin(rotation*DEG2RAD))*(shipHeight / 2.5f), position.y - static_cast<int>(cos(rotation*DEG2RAD))*(shipHeight / 2.5f), 12 };
		color = LIGHTGRAY;
		shipHeight = (10.0f) / static_cast<int>(tanf(20 * DEG2RAD));
		destroyedMeteorsCount = 0;
		for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
		{
				shoot[i]= NULL;
		}
	}

	void Player::Update()
	{
		speed.x = sin(rotation*DEG2RAD)*PlayerSpeed;
		speed.y = cos(rotation*DEG2RAD)*PlayerSpeed;

		position.x += (speed.x*acceleration);
		position.y -= (speed.y*acceleration);	

		if (position.x > screenWidth + shipHeight) position.x = -(shipHeight);
		else if (position.x < -(shipHeight)) position.x = screenWidth + shipHeight;
		if (position.y > (screenHeight + shipHeight)) position.y = -(shipHeight);
		else if (position.y < -(shipHeight)) position.y = screenHeight + shipHeight;
	}

	void Player::Draw()
	{
		shipHeight = (PlayerBaseSize / 2) / tanf(20 * DEG2RAD);
		Vector2 v1 = { position.x + sinf(rotation*DEG2RAD)*(shipHeight), position.y - cosf(rotation*DEG2RAD)*(shipHeight) };
		Vector2 v2 = { position.x - cosf(rotation*DEG2RAD)*(PlayerBaseSize / 2), position.y - sinf(rotation*DEG2RAD)*(PlayerBaseSize / 2) };
		Vector2 v3 = { position.x + cosf(rotation*DEG2RAD)*(PlayerBaseSize / 2), position.y + sinf(rotation*DEG2RAD)*(PlayerBaseSize / 2) };
		DrawTriangle(v1, v2, v3, MAROON);
		for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
		{
			if (shoot[i] != NULL)
			{
			shoot[i]->Draw();
			}
		}
	}

	
}