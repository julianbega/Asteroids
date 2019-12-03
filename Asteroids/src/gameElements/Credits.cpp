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
		DrawTexture(creditsTexture, 0, 0, WHITE);
	}
}