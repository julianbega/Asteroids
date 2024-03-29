#include "Game.h"
#include <iostream>
#include <math.h>
#include "raylib.h"
#include "gameElements/Global.h"
#include "gameObjects/Player.h"
namespace AsteroidsJ
{
	Game::Game()
	{
		

	}
	Game::~Game()
	{
		UnloadMusicStream(gameplayMusic);
		UnloadSound(AsteroidsBreack);
	}
	void Game::Init()
	{
		AsteroidsBreack = LoadSound("res/assets/sound/menuSelector.wav");
		player = new Player();
		gameOver = false;
		gameplayMusic = LoadMusicStream("res/assets/sound/gamePlayMusic.ogg");
		volume = 0.25f;
		SetMusicVolume(gameplayMusic, volume);
		destroyedMeteorsCount = 0;
		player->shipHeight = (10.0f) / tanf(20 * DEG2RAD);
		PlayMusicStream(gameplayMusic);
		victory = false;
		pause = false;
		midMeteorsCount = 0;
		smallMeteorsCount = 0;
		
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
		if (gameOver == false)
		{
			if (IsKeyPressed('P')) pause = !pause;

			if (!pause)
			{
				UpdateMusicStream(gameplayMusic);
				SetMusicVolume(gameplayMusic, volume);
				player->Input();
				player->Update();

				if (IsKeyPressed(KEY_SPACE))
				{
					for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
					{
						if (!shoot[i].active)
						{
							shoot[i].position = { player->position.x + sin(player->rotation*DEG2RAD)*(player->shipHeight), player->position.y - cos(player->rotation*DEG2RAD)*(player->shipHeight) };
							shoot[i].active = true;
							shoot[i].speed.x = static_cast<float>(1.5*sin(player->rotation*DEG2RAD)*player->playerSpeed);
							shoot[i].speed.y = static_cast<float>(1.5*cos(player->rotation*DEG2RAD)*player->playerSpeed);
							shoot[i].rotation = player->rotation;
							break;
						}
					}
				}

				for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
				{
					if (shoot[i].active) shoot[i].lifeSpawn++;
				}

				for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
				{
					if (shoot[i].active)
					{
						shoot[i].position.x += shoot[i].speed.x;
						shoot[i].position.y -= shoot[i].speed.y;

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

						if (shoot[i].lifeSpawn >= 60)
						{
							shoot[i].position = { 0, 0 };
							shoot[i].speed = { 0, 0 };
							shoot[i].lifeSpawn = 0;
							shoot[i].active = false;
						}
					}
				}

				player->collider = { player->position.x + sin(player->rotation*DEG2RAD)*(player->shipHeight / 2.5f), player->position.y - cos(player->rotation*DEG2RAD)*(player->shipHeight / 2.5f), 12 };

				for (int j = 0; j < MAX_BIG_METEORS; j++)
				{
					if (CheckCollisionCircles({ player->collider.x, player->collider.y }, player->collider.z, bigMeteor[j].position, bigMeteor[j].radius) && bigMeteor[j].active)
					{
						if (player->lives == 1)
						{
							gameOver = true;
						}
						else
						{
							player->lives = player->lives - 1;
						}

						bigMeteor[j].active = false;
						destroyedMeteorsCount++;
						PlaySound(AsteroidsBreack);

						for (int k = 0; k < 2; k++)
						{
							if (midMeteorsCount % 2 == 0)
							{
								mediumMeteor[midMeteorsCount].position = { bigMeteor[j].position.x, bigMeteor[j].position.y };
								mediumMeteor[midMeteorsCount].speed = { cos(player->rotation*DEG2RAD)*MeteorsSpeed*-1, sin(player->rotation*DEG2RAD)*MeteorsSpeed*-1 };
							}
							else
							{
								mediumMeteor[midMeteorsCount].position = { bigMeteor[j].position.x, bigMeteor[j].position.y };
								mediumMeteor[midMeteorsCount].speed = { cos(player->rotation*DEG2RAD)*MeteorsSpeed, sin(player->rotation*DEG2RAD)*MeteorsSpeed };
							}

							mediumMeteor[midMeteorsCount].active = true;
							midMeteorsCount++;
						}
						bigMeteor[j].color = RED;
						j = MAX_BIG_METEORS;
					}
				}

				for (int j = 0; j < MAX_MEDIUM_METEORS; j++)
				{
					if (CheckCollisionCircles({ player->collider.x, player->collider.y }, player->collider.z, mediumMeteor[j].position, mediumMeteor[j].radius) && mediumMeteor[j].active)
					{
						if (player->lives == 1)
						{
							gameOver = true;
						}
						else
						{
							player->lives = player->lives - 1;
						}
						mediumMeteor[j].active = false;
						destroyedMeteorsCount++;
						PlaySound(AsteroidsBreack);

						for (int k = 0; k < 2; k++)
						{
							if (smallMeteorsCount % 2 == 0)
							{
								smallMeteor[smallMeteorsCount].position = { mediumMeteor[j].position.x, mediumMeteor[j].position.y };
								smallMeteor[smallMeteorsCount].speed = { cos(player->rotation*DEG2RAD)*MeteorsSpeed*-1, sin(player->rotation*DEG2RAD)*MeteorsSpeed*-1 };
							}
							else
							{
								smallMeteor[smallMeteorsCount].position = { mediumMeteor[j].position.x, mediumMeteor[j].position.y };
								smallMeteor[smallMeteorsCount].speed = { cos(player->rotation*DEG2RAD)*MeteorsSpeed, sin(player->rotation*DEG2RAD)*MeteorsSpeed };
							}

							smallMeteor[smallMeteorsCount].active = true;
							smallMeteorsCount++;
						}
						mediumMeteor[j].color = GREEN;
						j = MAX_MEDIUM_METEORS;
					}
				}

				for (int j = 0; j < MAX_SMALL_METEORS; j++)
				{
					if (CheckCollisionCircles({ player->collider.x, player->collider.y }, player->collider.z, smallMeteor[j].position, smallMeteor[j].radius) && smallMeteor[j].active)
					{
						if (player->lives == 1)
						{
							gameOver = true;
						}
						else
						{
							player->lives = player->lives - 1;
						}
						smallMeteor[j].active = false;
						destroyedMeteorsCount++;
						PlaySound(AsteroidsBreack);
						smallMeteor[j].color = YELLOW;
						j = MAX_SMALL_METEORS;
					}
				}

				// si se salen de la pantalla aparecen del otro lado
				for (int i = 0; i < MAX_BIG_METEORS; i++)
				{
					if (bigMeteor[i].active)
					{
						bigMeteor[i].position.x += bigMeteor[i].speed.x;
						bigMeteor[i].position.y += bigMeteor[i].speed.y;

						if (bigMeteor[i].position.x > screenWidth + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
						else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = screenWidth + bigMeteor[i].radius;
						if (bigMeteor[i].position.y > screenHeight + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
						else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = screenHeight + bigMeteor[i].radius;
					}
				}
				// si se salen de la pantalla aparecen del otro lado
				for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
				{
					if (mediumMeteor[i].active)
					{
						mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
						mediumMeteor[i].position.y += mediumMeteor[i].speed.y;

						if (mediumMeteor[i].position.x > screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
						else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
						if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
						else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
					}
				}
				// si se salen de la pantalla aparecen del otro lado
				for (int i = 0; i < MAX_SMALL_METEORS; i++)
				{
					if (smallMeteor[i].active)
					{
						smallMeteor[i].position.x += smallMeteor[i].speed.x;
						smallMeteor[i].position.y += smallMeteor[i].speed.y;

						if (smallMeteor[i].position.x > screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
						else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
						if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
						else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
					}
				}


				// colision balas y asteroides
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
								PlaySound(AsteroidsBreack);

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
								PlaySound(AsteroidsBreack);

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
								PlaySound(AsteroidsBreack);
								smallMeteor[c].color = YELLOW;
								c = MAX_SMALL_METEORS;
							}
						}
					}
				}
			}
		}

		StopSound(AsteroidsBreack); 
		if (destroyedMeteorsCount == MAX_BIG_METEORS + MAX_MEDIUM_METEORS + MAX_SMALL_METEORS) victory = true;

		
			if (IsKeyPressed(KEY_ENTER))
			{
				Init();
				gameOver = false;
			}
			if (gameOver == true)
			{
				player->lives = 0;

			}
			if (IsKeyReleased(KEY_ESCAPE))
			{
				Init();
				gameOver = false;
				gamestatus = MENU;

			}



		return false;
	}
	void Game::Draw()
	{
		ClearBackground(RAYWHITE);
		
		for (int i = 0; i < MAX_BIG_METEORS; i++)
		{
			if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKBLUE);
			else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, Fade(BLUE, 0.3f));
		}

		for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
		{
			if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, DARKGREEN);
			else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, Fade(GREEN, 0.3f));
		}

		for (int i = 0; i < MAX_SMALL_METEORS; i++)
		{
			if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, DARKPURPLE);
			else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, Fade(PURPLE, 0.3f));
		}

		// Draw shoot
		for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
		{
			if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, BLACK);
		}

		if (victory) 
		{
			DrawText("VICTORY", screenWidth / 2 - MeasureText("VICTORY", 20) / 2, screenHeight / 2, 20, BLACK);
			DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
		}

		if (pause && gameOver == false) DrawText("PAUSED", screenWidth / 2 - MeasureText("PAUSED", 40) / 2, screenHeight / 2 - 40, 40, BLACK);
		
		if (player != NULL)
		{
			player->Draw();
		}
		if (gameOver)
		{
			DrawText("PRESS [ENTER] TO PLAY AGAIN", screenWidth / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, screenHeight / 2, 20, GRAY);
			DrawText("DEFEAT", GetScreenWidth() / 2 - MeasureText("DEFEAT", 20) / 2, GetScreenHeight() / 2 - 50, 20, BLACK);
		}
		
		

	}


}