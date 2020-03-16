#pragma once
#include "Game.h"
#include "State.h"
#include <thread>
namespace AT
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);
		~SplashState();
		void HandleInput();
		void Update(float dt);
		void Draw();
		void init();
		void loadnextstate();

	private:

		GameDataRef _data;
		sf::Sprite _background;
		sf::Clock _clock;

	};


}