#include "Game.h"
#include "SplashState.h"
namespace AT
{
	Game::Game(int width, int height, std::string title)
	{
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar| sf::Style::Resize);
		_data->machine.AddState(StateRef(new SplashState(_data)));
		_data->window.setFramerateLimit(FPS);
		sf::Image icon;
		icon.loadFromFile(ICON_PATH);
		_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		run();
	}
	void Game::run()
	{
		bool draw = true;
		float accumulateur =0;
		float newtime;
		float currenttime = _clock.getElapsedTime().asSeconds();
		float frametime;
		while (_data->window.isOpen())
		{
			_data->machine.ProcessStateChanges();
			newtime = _clock.getElapsedTime().asSeconds();
			frametime = newtime - currenttime;
			currenttime = newtime;
			if (frametime > 0.25f)
				frametime = 0.25f;
			accumulateur += frametime;
			while (accumulateur>=dt)
			{
				_data->machine.CurrentState()->HandleInput();
				_data->machine.CurrentState()->Update(dt);
				accumulateur -= dt;
				draw = true;
			}
			if (draw)
			{
				_data->machine.CurrentState()->Draw();
			}
			draw = false;

		}
	}
}