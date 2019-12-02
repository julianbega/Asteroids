#include "Game.h"
#include "raylib.h"
#include "GamePlay.h"
#include "Menu.h"
#include "Credits.h"
#include "Global.h"

namespace AsteroidsJ
{
	Game::Game()
	{
		InitWindow(screenWidth, screenHeight, "Asteroids v0.1");
		InitAudioDevice();
		gamePlay = new GamePlay();
		menu = new Menu();
		credits = new Credits();
		inGame = true;

	}

	Game::~Game()
	{
		if (gamePlay) delete gamePlay;
		if (menu) delete menu;
		if (credits) delete credits;
		CloseAudioDevice();
		CloseWindow();
	}
	void Game::Play()
	{
		Init();
		while (inGame)
		{

			Update();
			Draw();
		}
	}
	void Game::Init()
	{
		menu->Init();
		gamePlay->Init();
		credits->Init();
		gamestatus = MENU;
	}
	void Game::Update()
	{
		switch (gamestatus)
		{
		case MENU:
			menu->Update();
			break;
		case GAME:
			if (!firstTime)
			{
				firstTime = true;
				gamePlay->Init();
			}
			if (gamePlay->Update())
			{
				gamestatus = CREDITS;
				menu->changeIsControlMenu();
				firstTime = false;
				PlaySound(winSong);
			}
			break;
		case CREDITS:
			credits->Update();
			break;
		case EXIT:
			inGame = false;
			break;
		}
	}
	void Game::Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		switch (gamestatus)
		{
		case MENU:
			menu->Draw();
			break;
		case GAME:
			gamePlay->Draw();
			break;
		case CREDITS:
			credits->Draw();
			break;
		}
		EndDrawing();
	}
}