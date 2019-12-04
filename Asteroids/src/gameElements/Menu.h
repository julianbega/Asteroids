#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include "gameObjects/Player.h"
namespace AsteroidsJ
{
	
	class Menu
	{
		enum MenuOptions
		{
			Play, Credits, Exit, None
		};
	public:
		Menu();
		~Menu();
		void Init();
		void Input();
		void Update();
		void Draw();
		int actualOption;
		float volume;
		Player* player;

		Rectangle PlayerRec;
		Rectangle PlayRec;
		Rectangle CreditsRec;
		Rectangle ExitRec;
	private:
		Sound menuSelectorSound;
		Music menuMusic;
		Texture2D titleTexture;
		Texture2D controlsTexture;


	};
	

	//
}
#endif