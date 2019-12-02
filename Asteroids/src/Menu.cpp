#include "Menu.h"
#include "raylib.h"
#include "Global.h"
namespace AsteroidsJ
{
	Menu::Menu()
	{
		
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