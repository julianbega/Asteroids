#include "Credits.h"
#include "raylib.h"
#include "Global.h"
namespace AsteroidsJ
{
	Credits::Credits()
	{
		creditsTexture = LoadTexture("res/assets/img/Creditos.png");
		creditsTexture.width = GetScreenWidth();
		creditsTexture.height = GetScreenHeight();
	}

	Credits::~Credits()
	{
	}
	void Credits::Init()
	{
	}
	void Credits::Input()
	{
		if (IsKeyReleased(KEY_ENTER))
		{
			gamestatus = MENU;
		}
		if (IsKeyReleased(KEY_ESCAPE))
		{
			gamestatus = MENU;
		}
	}
	void Credits::Update()
	{
		Input();
	}
	void Credits::Draw()
	{
		DrawText("Asteroids", GetScreenWidth()/4 , GetScreenHeight()/5, tilescale*2, WHITE);
		DrawText("Enter: Menu", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY), tilescale, WHITE);
		DrawText("ESC: Back", GetScreenWidth() - (tilescale * CONTROLESTEXTDISTANCEINY), (tilescale * EXITTEXTDISTANCEINY) - tilescale, tilescale, WHITE);
		DrawText("https: //patrickdearteaga.com ", + (tilescale), (tilescale * EXITTEXTDISTANCEINY), tilescale/2, WHITE);
		DrawText("Julian Bega", + (tilescale ), (tilescale * EXITTEXTDISTANCEINY) - tilescale, tilescale/2, WHITE);
	}
}