#include "Menu.h"
#include "raylib.h"
#include "Global.h"
namespace AsteroidsJ
{
	Menu::Menu()
	{
		menuSelectorSound = LoadSound("res/assets/sound/menuSelector.wav");
		menuMusic = LoadMusicStream("res/assets/sound/menuMusic.ogg");
		titleTexture.height = titleTexture.height / 2;
		titleTexture.width = titleTexture.width / 2;
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
		player = new Player();
		actualOption = None;
		PlayMusicStream(menuMusic);
		player->shipHeight = (10.0f) / tanf(20 * DEG2RAD);
		PlayRec.x = tilescale * TEXTDISTANCEINX;
		PlayRec.y = tilescale * PLAYTEXTDISTANCEINY;
		PlayRec.width = tilescale*2.3;
		PlayRec.height = tilescale;

		CreditsRec.x = tilescale * TEXTDISTANCEINX;
		CreditsRec.y = tilescale * CREDITSTEXTDISTANCEINY;
		CreditsRec.width = tilescale * 3.7;
		CreditsRec.height = tilescale;

		ExitRec.x = tilescale * TEXTDISTANCEINX;
		ExitRec.y = tilescale * EXITTEXTDISTANCEINY;
		ExitRec.width = tilescale * 2;
		ExitRec.height = tilescale;


	}

	void Menu::Input()
	{
		
		if (IsKeyReleased(KEY_ESCAPE))
		{
			gamestatus = END;
		}
		if (IsKeyReleased(KEY_ENTER))
		{
			
				switch (actualOption)
				{
				case Play:
					gamestatus = GAME;
					StopSound(menuSelectorSound);
					StopMusicStream(menuMusic);
				
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
		player->Input();
		player->Update();
		PlayerRec.x = player->position.x;
		PlayerRec.y = player->position.y;
		PlayerRec.width = player->PlayerBaseSize;
		PlayerRec.height = player->PlayerBaseSize;
		if (CheckCollisionRecs(PlayRec, PlayerRec))
		{
			actualOption = Play;
		}
		else if (CheckCollisionRecs(CreditsRec, PlayerRec))
		{
			actualOption = Credits;
		}
		else if (CheckCollisionRecs(ExitRec, PlayerRec))
		{
			actualOption = Exit;
		}
		else
		{
			actualOption = None;
		}
	}

	void Menu::Draw()
	{
		if (player != NULL)
		{
			player->Draw();
		}
			
			DrawTexture(titleTexture, GetScreenWidth() / 2 - titleTexture.width / 2,
				GetScreenHeight() / 5 - titleTexture.height / 2, WHITE);
		
			switch (actualOption)
			{
			case Play:
				DrawText("Play", tilescale * TEXTDISTANCEINX, tilescale * PLAYTEXTDISTANCEINY, tilescale, YELLOW);
				DrawText("Credits", tilescale * TEXTDISTANCEINX, tilescale * CREDITSTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Exit", tilescale * TEXTDISTANCEINX, tilescale * EXITTEXTDISTANCEINY, tilescale, WHITE);
				break;

			case Credits:
				DrawText("Play", tilescale * TEXTDISTANCEINX, tilescale * PLAYTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Credits", tilescale * TEXTDISTANCEINX, tilescale * CREDITSTEXTDISTANCEINY, tilescale, YELLOW);
				DrawText("Exit", tilescale * TEXTDISTANCEINX, tilescale * EXITTEXTDISTANCEINY, tilescale, WHITE);
				break;

			case Exit:
				DrawText("Play", tilescale * TEXTDISTANCEINX, tilescale * PLAYTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Credits", tilescale * TEXTDISTANCEINX, tilescale * CREDITSTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Exit", tilescale * TEXTDISTANCEINX, tilescale * EXITTEXTDISTANCEINY, tilescale, YELLOW);
				break;
			default:
				DrawText("Play", tilescale * TEXTDISTANCEINX, tilescale * PLAYTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Credits", tilescale * TEXTDISTANCEINX, tilescale * CREDITSTEXTDISTANCEINY, tilescale, WHITE);
				DrawText("Exit", tilescale * TEXTDISTANCEINX, tilescale * EXITTEXTDISTANCEINY, tilescale, WHITE);
				break;
			}
			
			DrawText("Asteroids", GetScreenWidth() / 4, GetScreenHeight() / 5, tilescale * 2, WHITE);
			DrawText("F2 - volume", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), tilescale * EXITTEXTDISTANCEINY, tilescale, WHITE);
			DrawText("F3 + volume", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY) + tilescale, tilescale, WHITE);
			DrawText("Move: Arrows", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY) - tilescale, tilescale, WHITE);
			DrawText("Space: Shoot", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY) - 2 * tilescale, tilescale, WHITE);
			DrawText("Enter: Reset", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY) - 3*tilescale, tilescale, WHITE);
			DrawText("P: Pause", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY) - 4 * tilescale, tilescale, WHITE);
			DrawText("ESC: Back", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY) - 5 * tilescale, tilescale, WHITE);
		
	}

	
}