#include "Menu.h"
#include "raylib.h"
#include "Global.h"
namespace AsteroidsJ
{
	Menu::Menu()
	{
		menuSelectorSound = LoadSound("assets/sound/menuSelector.wav");
		menuMusic = LoadMusicStream("assets/sound/menuMusic.ogg");
		titleTexture = LoadTexture("assets/img/Titulo para el menu.png");
		titleTexture.height = titleTexture.height / 2;
		titleTexture.width = titleTexture.width / 2;
		controlsTexture = LoadTexture("assets/img/Controls.png");
		controlsTexture.width = GetScreenWidth();
		controlsTexture.height = GetScreenHeight();
		volume = 0.25f;
		SetMusicVolume(menuMusic, volume);

	}

	Menu::~Menu()
	{
		UnloadSound(menuSelectorSound);
		UnloadTexture(titleTexture);
		UnloadMusicStream(menuMusic);
	}

	void Menu::Init()
	{
		actualOption = Play;
		isControlMenu = false;
		PlayMusicStream(menuMusic);
	}

	void Menu::Input()
	{
		if (IsKeyReleased(KEY_W))
		{
			PlaySound(menuSelectorSound);

			if (actualOption == Play)
			{
				actualOption = Exit;
			}
			else
			{
				actualOption--;
			}
		}
		if (IsKeyReleased(KEY_S))
		{
			PlaySound(menuSelectorSound);

			if (actualOption == Exit)
			{
				actualOption = Play;
			}
			else
			{
				actualOption++;
			}
		}
		if (IsKeyReleased(KEY_ENTER))
		{
			if (isControlMenu == false)
			{
				switch (actualOption)
				{
				case Play:
					gamestatus = GAME;
					StopSound(menuSelectorSound);
					StopMusicStream(menuMusic);
				case Controls:
					isControlMenu = true;
					break;

				case Credits:
					gamestatus = CREDITS;
					break;

				case Exit:
					gamestatus = EXIT;
					break;
				default:
					break;
				}
			}
			else
			{
				changeIsControlMenu();
			}
		}
		if (IsKeyDown(KEY_ESCAPE) && isControlMenu == true)
		{
			isControlMenu = false;
		}
		if (IsKeyReleased(KEY_F3))
		{
			if (volume <= 1.00f)
			{
				volume = volume + 0.1f;
			}
		}
		if (IsKeyReleased(KEY_F2))
		{
			if (volume >= 0.00f)
			{
				volume = volume - 0.1f;
			}
		}

	}

	void Menu::Update()
	{
		UpdateMusicStream(menuMusic);
		SetMusicVolume(menuMusic, volume);
		Input();

	}

	void Menu::Draw()
	{
		if (isControlMenu == false)
		{
			int tilescale = static_cast<int>(tileScale);
			DrawTexture(titleTexture, GetScreenWidth() / 2 - titleTexture.width / 2,
				GetScreenHeight() / 5 - titleTexture.height / 2, WHITE);
			switch (actualOption)
			{
			case Play:
				DrawText("Play", tilescale * TEXTDISTANCEINX, tilescale * PLAYTEXTDISTANCEINY, tilescale, YELLOW);
				DrawText("Controls", tilescale * TEXTDISTANCEINX, tilescale * CONTROLESTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Credits", tilescale * TEXTDISTANCEINX, tilescale * CREDITSTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Exit", tilescale * TEXTDISTANCEINX, tilescale * EXITTEXTDISTANCEINY, tilescale, WHITE);
				break;

			case Controls:
				DrawText("Play", tilescale * TEXTDISTANCEINX, tilescale * PLAYTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Controls", tilescale * TEXTDISTANCEINX, tilescale * CONTROLESTEXTDISTANCEINY, tilescale, YELLOW);
				DrawText("Credits", tilescale * TEXTDISTANCEINX, tilescale * CREDITSTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Exit", tilescale * TEXTDISTANCEINX, tilescale * EXITTEXTDISTANCEINY, tilescale, WHITE);
				break;

			case Credits:
				DrawText("Play", tilescale * TEXTDISTANCEINX, tilescale * PLAYTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Controls", tilescale * TEXTDISTANCEINX, tilescale * CONTROLESTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Credits", tilescale * TEXTDISTANCEINX, tilescale * CREDITSTEXTDISTANCEINY, tilescale, YELLOW);
				DrawText("Exit", tilescale * TEXTDISTANCEINX, tilescale * EXITTEXTDISTANCEINY, tilescale, WHITE);
				break;

			case Exit:
				DrawText("Play", tilescale * TEXTDISTANCEINX, tilescale * PLAYTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Controls", tilescale * TEXTDISTANCEINX, tilescale * CONTROLESTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Credits", tilescale * TEXTDISTANCEINX, tilescale * CREDITSTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Exit", tilescale * TEXTDISTANCEINX, tilescale * EXITTEXTDISTANCEINY, tilescale, YELLOW);
				break;
			default:
				break;
			}
			DrawText("F2 - volume", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), tilescale * EXITTEXTDISTANCEINY, tilescale, WHITE);
			DrawText("F3 + volume", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY) + tilescale, tilescale, WHITE);
		}
		else
		{
			DrawTexture(controlsTexture, 0, 0, WHITE);
		}
	}

	bool Menu::getIsControlMenu()
	{
		return isControlMenu;
	}

	void Menu::changeIsControlMenu()
	{
		isControlMenu = !isControlMenu;
	}

}