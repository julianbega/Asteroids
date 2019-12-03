#include "Game.h"
#include <iostream>
#include "raylib.h"
#include "gameElements/Global.h"
#include "gameObjects/Player.h"
#include "gameObjects/Bullet.h"
#include "gameObjects/Meteor.h"
#include "gameObjects/MediumMeteor.h"
#include "gameObjects/SmallMeteor.h"

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
		shipHeight = (10.0f) / tanf(20 * DEG2RAD);
		PlayMusicStream(gameMusic);
		victory = false;
		pause = false;
		midMeteorsCount = 0;
		smallMeteorsCount = 0;
		for (int i = 0; i < MAX_BIG_METEORS; i++)
		{
			bigMeteor[i]->Init();
		}
		for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
		{
			mediumMeteor[i]= NULL;
		}
		for (int i = 0; i < MAX_SMALL_METEORS; i++)
		{
			smallMeteor[i] = NULL;
		}
	}
	bool Game::Update()
	{
		if (IsKeyPressed('P')) pause = !pause;

		
		UpdateMusicStream(gameMusic);
		SetMusicVolume(gameMusic, volume);
		player->Input();
		player->Update();
		
		if (IsKeyDown(KEY_ESCAPE))
		{
			gamestatus = MENU;

		}
		if (!pause)
		{
		}
		
		return false;
	}
	void Game::Draw()
	{
		ClearBackground(RAYWHITE);
		player->Draw();
		
		for (int i = 0; i < MAX_BIG_METEORS; i++)
		{
			if (mediumMeteor[i] != NULL)
			{
			bigMeteor[i]->Draw();
			}
		}
		
		for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
		{
			if (mediumMeteor[i] != NULL)
			{
			mediumMeteor[i]->Draw();
			}
		}
		for (int i = 0; i < MAX_SMALL_METEORS; i++)
		{
			if (smallMeteor[i] != NULL)
			{
			smallMeteor[i]->Draw();
			}
		}

		
				
			
		
				
			

			if (victory) gameOver = !gameOver;

			if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
		

	}





	/*
	void UpdateGame()
	{
		
			
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
				player.collider = { player.position.x + static_cast<float>(sin(player.rotation*DEG2RAD))*(shipHeight / 2.5f), player.position.y - static_cast<float>(cos(player.rotation*DEG2RAD))*(shipHeight / 2.5f), 12 };

				for (int a = 0; a < MAX_BIG_METEORS; a++)
				{
					if (CheckCollisionCircles({ player.collider.x, player.collider.y }, player.collider.z, bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active) gameOver = true;
				}

				for (int a = 0; a < MAX_MEDIUM_METEORS; a++)
				{
					if (CheckCollisionCircles({ player.collider.x, player.collider.y }, player.collider.z, mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active) gameOver = true;
				}

				for (int a = 0; a < MAX_SMALL_METEORS; a++)
				{
					if (CheckCollisionCircles({ player.collider.x, player.collider.y }, player.collider.z, smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active) gameOver = true;
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
										mediumMeteor[midMeteorsCount].speed = { static_cast<float>(cos(shoot[i].rotation*DEG2RAD))*METEORS_SPEED*-1, static_cast<float>(sin(shoot[i].rotation*DEG2RAD))*METEORS_SPEED*-1 };
									}
									else
									{
										mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
										mediumMeteor[midMeteorsCount].speed = { static_cast<float>(cos(shoot[i].rotation*DEG2RAD))*METEORS_SPEED, static_cast<float>(sin(shoot[i].rotation*DEG2RAD))*METEORS_SPEED };
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
										smallMeteor[smallMeteorsCount].speed = { static_cast<float>(cos(shoot[i].rotation*DEG2RAD))*METEORS_SPEED*-1, static_cast<float>(sin(shoot[i].rotation*DEG2RAD))*METEORS_SPEED*-1 };
									}
									else
									{
										smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
										smallMeteor[smallMeteorsCount].speed = { static_cast<float>(cos(shoot[i].rotation*DEG2RAD))*METEORS_SPEED, static_cast<float>(sin(shoot[i].rotation*DEG2RAD))*METEORS_SPEED };
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
	*/


}
