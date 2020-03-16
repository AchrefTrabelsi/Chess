#pragma once
#include "State.h"
#include "Game.h"
#include "Definitions.h"
#include <thread>
namespace AT
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		void HandleInput();
		void Update(float dt);
		void Draw();
		void init();
		void loadnextstate();
		void resize();
	private:
		sf::Sprite _PlayButton;
		sf::Sprite _QuitButton;
		sf::Sprite _Background;
		std::string FocusedButton;
		bool ButtonPressed;
		bool ButtonReleased;
		sf::Vector2i MousePos;
		GameDataRef _data;

	};

}