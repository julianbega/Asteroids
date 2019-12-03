#include "Game.h"
#include <iostream>
#include "raylib.h"
#include "gameElements/Global.h"
#include "gameObjects/Player.h"
//#include "gameObjects/Bullet.h"
//#include "gameObjects/Meteor.h"
//#include "gameObjects/MediumMeteor.h"
//#include "gameObjects/SmallMeteor.h"

namespace AsteroidsJ
{
	Game::Game()
	{
		

	}
	Game::~Game()
	{
		UnloadMusicStream(gameMusic);
		UnloadSound(resetSong);
	}
	void Game::Init()
	{
		player = new Player();
		gameOver = false;
		gameMusic = LoadMusicStream("res/assets/sound/gamePlayMusic.ogg");
		resetSong = LoadSound("res/assets/sound/resetSong.wav");
		volume = 0.25f;
		SetMusicVolume(gameMusic, volume);
		destroyedMeteorsCount = 0;
		player->shipHeight = (10.0f) / tanf(20 * DEG2RAD);
		PlayMusicStream(gameMusic);
		victory = false;
		pause = false;
		midMeteorsCount = 0;
		smallMeteorsCount = 0;
		



		////////////////////////////////////////////


		int posx, posy;
		int velx, vely;
		bool correctRange = false;
		victory = false;
		pause = false;


		destroyedMeteorsCount = 0;

		for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
		{
			shoot[i].position = { 0, 0 };
			shoot[i].speed = { 0, 0 };
			shoot[i].radius = 2;
			shoot[i].active = false;
			shoot[i].lifeSpawn = 0;
			shoot[i].color = WHITE;
		}

		for (int i = 0; i < MAX_BIG_METEORS; i++)
		{
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

			bigMeteor[i].position =  { static_cast<float>(posx), static_cast<float>(posy) };

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

			bigMeteor[i].speed = { static_cast<float>(velx), static_cast<float>(vely) }; 
			bigMeteor[i].radius = 40;
			bigMeteor[i].active = true;
			bigMeteor[i].color = BLUE;
		}

		for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
		{
			mediumMeteor[i].position = { -100, -100 };
			mediumMeteor[i].speed = { 0, 0 };
			mediumMeteor[i].radius = 20;
			mediumMeteor[i].active = false;
			mediumMeteor[i].color = BLUE;
		}

		for (int i = 0; i < MAX_SMALL_METEORS; i++)
		{
			smallMeteor[i].position = { -100, -100 };
			smallMeteor[i].speed = { 0, 0 };
			smallMeteor[i].radius = 10;
			smallMeteor[i].active = false;
			smallMeteor[i].color = BLUE;
		}

	}
	bool Game::Update()
	{

		if (IsKeyPressed('P')) pause = !pause;

		if (!pause)
		{
			UpdateMusicStream(gameMusic);
			SetMusicVolume(gameMusic, volume);
			player->Input();
			player->Update();

			if (IsKeyDown(KEY_ESCAPE))
			{
				gamestatus = MENU;

			}
			if (IsKeyPressed(KEY_SPACE))
			{
				for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
				{
					if (!shoot[i].active)
					{
						shoot[i].position = { player->position.x + sin(player->rotation*DEG2RAD)*(player->shipHeight), player->position.y - cos(player->rotation*DEG2RAD)*(player->shipHeight) };
						shoot[i].active = true;
						shoot[i].speed.x = 1.5*sin(player->rotation*DEG2RAD)*player->PlayerSpeed;
						shoot[i].speed.y = 1.5*cos(player->rotation*DEG2RAD)*player->PlayerSpeed;
						shoot[i].rotation = player->rotation;
						break;
					}
				}
			}

			// Shoot life timer
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if (shoot[i].active) shoot[i].lifeSpawn++;
			}

			// Shot logic
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if (shoot[i].active)
				{
					// Movement
					shoot[i].position.x += shoot[i].speed.x;
					shoot[i].position.y -= shoot[i].speed.y;

					// Collision logic: shoot vs walls
					if (shoot[i].position.x > screenWidth + shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					else if (shoot[i].position.x < 0 - shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					if (shoot[i].position.y > screenHeight + shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					else if (shoot[i].position.y < 0 - shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}

					// Life of shoot
					if (shoot[i].lifeSpawn >= 60)
					{
						shoot[i].position = { 0, 0 };
						shoot[i].speed = { 0, 0 };
						shoot[i].lifeSpawn = 0;
						shoot[i].active = false;
					}
				}
			}

			// Collision logic: player vs meteors
			player->collider = { player->position.x + sin(player->rotation*DEG2RAD)*(player->shipHeight / 2.5f), player->position.y - cos(player->rotation*DEG2RAD)*(player->shipHeight / 2.5f), 12 };

			for (int a = 0; a < MAX_BIG_METEORS; a++)
			{
				if (CheckCollisionCircles({ player->collider.x, player->collider.y }, player->collider.z, bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active) gameOver = true;
			}

			for (int a = 0; a < MAX_MEDIUM_METEORS; a++)
			{
				if (CheckCollisionCircles({ player->collider.x, player->collider.y }, player->collider.z, mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active) gameOver = true;
			}

			for (int a = 0; a < MAX_SMALL_METEORS; a++)
			{
				if (CheckCollisionCircles({ player->collider.x, player->collider.y }, player->collider.z, smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active) gameOver = true;
			}

			// Meteors logic: big meteors
			for (int i = 0; i < MAX_BIG_METEORS; i++)
			{
				if (bigMeteor[i].active)
				{
					// Movement
					bigMeteor[i].position.x += bigMeteor[i].speed.x;
					bigMeteor[i].position.y += bigMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (bigMeteor[i].position.x > screenWidth + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = screenWidth + bigMeteor[i].radius;
					if (bigMeteor[i].position.y > screenHeight + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = screenHeight + bigMeteor[i].radius;
				}
			}

			// Meteors logic: medium meteors
			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				if (mediumMeteor[i].active)
				{
					// Movement
					mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
					mediumMeteor[i].position.y += mediumMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (mediumMeteor[i].position.x > screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
					else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
					if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
					else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
				}
			}

			// Meteors logic: small meteors
			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				if (smallMeteor[i].active)
				{
					// Movement
					smallMeteor[i].position.x += smallMeteor[i].speed.x;
					smallMeteor[i].position.y += smallMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (smallMeteor[i].position.x > screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
					else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
					if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
					else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
				}
			}

			// Collision logic: player-shoots vs meteors
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if ((shoot[i].active))
				{
					for (int a = 0; a < MAX_BIG_METEORS; a++)
					{
						if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							bigMeteor[a].active = false;
							destroyedMeteorsCount++;

							for (int j = 0; j < 2; j++)
							{
								if (midMeteorsCount % 2 == 0)
								{
									mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
									mediumMeteor[midMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*MeteorsSpeed*-1, sin(shoot[i].rotation*DEG2RAD)*MeteorsSpeed*-1 };
								}
								else
								{
									mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
									mediumMeteor[midMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*MeteorsSpeed, sin(shoot[i].rotation*DEG2RAD)*MeteorsSpeed };
								}

								mediumMeteor[midMeteorsCount].active = true;
								midMeteorsCount++;
							}
							//bigMeteor[a].position = (Vector2){-100, -100};
							bigMeteor[a].color = RED;
							a = MAX_BIG_METEORS;
						}
					}

					for (int b = 0; b < MAX_MEDIUM_METEORS; b++)
					{
						if (mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, mediumMeteor[b].position, mediumMeteor[b].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							mediumMeteor[b].active = false;
							destroyedMeteorsCount++;

							for (int j = 0; j < 2; j++)
							{
								if (smallMeteorsCount % 2 == 0)
								{
									smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
									smallMeteor[smallMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*MeteorsSpeed*-1, sin(shoot[i].rotation*DEG2RAD)*MeteorsSpeed*-1 };
								}
								else
								{
									smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
									smallMeteor[smallMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*MeteorsSpeed, sin(shoot[i].rotation*DEG2RAD)*MeteorsSpeed };
								}

								smallMeteor[smallMeteorsCount].active = true;
								smallMeteorsCount++;
							}
							//mediumMeteor[b].position = (Vector2){-100, -100};
							mediumMeteor[b].color = GREEN;
							b = MAX_MEDIUM_METEORS;
						}
					}

					for (int c = 0; c < MAX_SMALL_METEORS; c++)
					{
						if (smallMeteor[c].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, smallMeteor[c].position, smallMeteor[c].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							smallMeteor[c].active = false;
							destroyedMeteorsCount++;
							smallMeteor[c].color = YELLOW;
							// smallMeteor[c].position = (Vector2){-100, -100};
							c = MAX_SMALL_METEORS;
						}
					}
				}
			}
		}

		if (destroyedMeteorsCount == MAX_BIG_METEORS + MAX_MEDIUM_METEORS + MAX_SMALL_METEORS) victory = true;

		else
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				Init();
				gameOver = false;
			}
		}


		return false;
	}
	void Game::Draw()
	{
		ClearBackground(RAYWHITE);
		if (player != NULL)
		{ 
		player->Draw();
		}
		for (int i = 0; i < MAX_BIG_METEORS; i++)
		{
			if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
			else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
		}

		for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
		{
			if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, GRAY);
			else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
		}

		for (int i = 0; i < MAX_SMALL_METEORS; i++)
		{
			if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, GRAY);
			else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
		}

		// Draw shoot
		for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
		{
			if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, BLACK);
		}

		if (victory) DrawText("VICTORY", screenWidth / 2 - MeasureText("VICTORY", 20) / 2, screenHeight / 2, 20, LIGHTGRAY);

		if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
	
		else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);


	}

}