#include "GamePlay.h"
#include <iostream>
#include "raylib.h"
#include "Global.h"
#include "Player.h"

namespace AsteroidsJ
{
	GamePlay::GamePlay()
	{
		player = new Player();
		gameMusic = LoadMusicStream("assets/sound/gamePlayMusic.ogg");
		resetSong = LoadSound("assets/sound/resetSong.wav");
		SetMusicVolume(gameMusic, 0.25);
	}
	GamePlay::~GamePlay()
	{
		UnloadMusicStream(gameMusic);
		UnloadSound(resetSong);
		if (player) delete player;
	}
	void GamePlay::Init()
	{
		player = new Player();
		PlayMusicStream(gameMusic);
	}
	bool GamePlay::Update()
	{
		UpdateMusicStream(gameMusic);
		SetMusicVolume(gameMusic, 0.25);
		if (IsKeyDown(KEY_ESCAPE))
		{
			gamestatus = MENU;
			if (!IsSoundPlaying(resetSong))
			{
				PlaySound(resetSong);
			}
		}
		
		return false;
	}
	void GamePlay::Draw()
	{
		player->Draw();
	}
}