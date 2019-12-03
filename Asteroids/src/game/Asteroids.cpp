#include "Asteroids.h"
#include "raylib.h"
#include "gameElements/Game.h"
#include "gameElements/Menu.h"
#include "gameElements/Credits.h"
#include "gameElements/Global.h"

namespace AsteroidsJ
{
	Asteroids::Asteroids()
	{
		InitWindow(screenWidth, screenHeight, "Asteroids");
		InitAudioDevice();
		game = new Game();
		menu = new Menu();
		credits = new Credits();
		inGame = true;
		SetExitKey(KEY_BACK);

	}

	Asteroids::~Asteroids()
	{

		if (game) delete game;
		if (menu) delete menu;
		if (credits) delete credits;
		CloseAudioDevice();
		CloseWindow();
	}
	void Asteroids::Play()
	{
		Init();
		while (inGame && !WindowShouldClose())
		{

			Update();
			Draw();
		}
	}
	void Asteroids::Init()
	{
		menu->Init();
		credits->Init();
		gamestatus = MENU;
		SetTargetFPS(60);
	}
	void Asteroids::Update()
	{
		switch (gamestatus)
		{
		case MENU:
			menu->Update();
			break;
		case GAME:
			if (!firstTime)
			{
				menu->Init();
				firstTime = true;
				game->Init();
			}
			if (game->Update())
			{
				/*gamestatus = CREDITS;
				firstTime = false;
				PlaySound(winSong);
				*/
			}
			break;
		case CREDITS:
			credits->Update();
			break;
		case EXIT:
			inGame = false;
			break;
		case END:
			inGame = false;
			break;
		}
	}
	void Asteroids::Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		switch (gamestatus)
		{
		case MENU:
			menu->Draw();
			break;
		case GAME:
			game->Draw();
			break;
		case CREDITS:
			credits->Draw();
			break;
		}
		EndDrawing();
	}
}