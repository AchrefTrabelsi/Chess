#pragma once
#include <memory>
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
#include "InputHandler.h"
#include "AssetManager.h"
#include "Definitions.h"

namespace AT
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputHandler input;
	};
	typedef std::shared_ptr<GameData> GameDataRef;
	class Game
	{
	public:
		Game(int width , int height , std::string title);

	private:
		const float dt = 1.0f / FPS;
		sf::Clock _clock;
		GameDataRef _data = std::make_shared<GameData>();
		void run();	

	};
}
