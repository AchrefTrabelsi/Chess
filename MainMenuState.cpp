#include "MainMenuState.h"
#include "GameState.h"
#define Bscale 1
namespace AT
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{
		FocusedButton = "";
		ButtonPressed = false;
		ButtonReleased = false;
		_QuitButton.setTexture(_data->assets.GetTexture("QuitButton"));
		_PlayButton.setTexture(_data->assets.GetTexture("PlayButton"));
		_Background.setTexture(_data->assets.GetTexture("Background"));
		_QuitButton.setOrigin(_QuitButton.getGlobalBounds().width / 2, _QuitButton.getGlobalBounds().height / 2);
		_PlayButton.setOrigin(_PlayButton.getGlobalBounds().width / 2, _PlayButton.getGlobalBounds().height / 2);

	}
	void MainMenuState::HandleInput()
	{
		sf::Event e;
		while (_data->window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			else if (e.type == sf::Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					ButtonPressed = true;
					MousePos = _data->input.MousePosition(_data->window);
				}
			}
			else if (e.type == sf::Event::MouseButtonReleased)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					MousePos = _data->input.MousePosition(_data->window);
					ButtonPressed = false;
					ButtonReleased = true;
				}
			}
			else if (e.type == sf::Event::Resized)
			{
				if (e.size.height > WindowHeight || e.size.width > WindowWidth)
				{
					WindowHeight = fmaxf(e.size.height, e.size.width);
					WindowWidth = fmaxf(e.size.height, e.size.width);
				}
				else
				{
					WindowHeight = fminf(e.size.height, e.size.width);
					WindowWidth = fminf(e.size.height, e.size.width);
				}
				_data->window.setSize(sf::Vector2u(WindowWidth, WindowHeight));
				resize();
			}

		}
	}
	void MainMenuState::Update(float dt)
	{
		sf::Vector2i CurrentMousePos = _data->input.MousePosition(_data->window);
		if (ButtonPressed)
		{
			if (_PlayButton.getGlobalBounds().contains(MousePos.x, MousePos.y))
			{
				FocusedButton = "PlayButton";
			}
			else if (_QuitButton.getGlobalBounds().contains(MousePos.x, MousePos.y))
			{
				FocusedButton = "QuitButton";
			}
		}
		if (_PlayButton.getGlobalBounds().contains(CurrentMousePos.x, CurrentMousePos.y))
		{
			_QuitButton.setTexture(_data->assets.GetTexture("QuitButton"));
			if (FocusedButton == "PlayButton")
			{
				_PlayButton.setTexture(_data->assets.GetTexture("PlayButtonClicked"));
			}
			else
			{
				_PlayButton.setTexture(_data->assets.GetTexture("PlayButtonHover"));
			}
		}
		else if (_QuitButton.getGlobalBounds().contains(CurrentMousePos.x, CurrentMousePos.y))
		{
			_PlayButton.setTexture(_data->assets.GetTexture("PlayButton"));

			if (FocusedButton == "QuitButton")
			{
				_QuitButton.setTexture(_data->assets.GetTexture("QuitButtonClicked"));
			}
			else
			{
				_QuitButton.setTexture(_data->assets.GetTexture("QuitButtonHover"));
			}

		}
		else
		{
			_PlayButton.setTexture(_data->assets.GetTexture("PlayButton"));
			_QuitButton.setTexture(_data->assets.GetTexture("QuitButton"));

		}


		if (ButtonReleased)
		{
			if (FocusedButton == "PlayButton")
			{
				if (_PlayButton.getGlobalBounds().contains(MousePos.x, MousePos.y))
				{
					nextstateloader.join();
					_data->machine.AddState(StateRef(nextstate));
				}
			}
			else if (FocusedButton == "QuitButton")
			{
				if (_QuitButton.getGlobalBounds().contains(MousePos.x, MousePos.y))
				{
					_data->window.close();
				}
			}
			ButtonReleased = false;
			FocusedButton = "";

		}
	}
	void MainMenuState::Draw()
	{
		_data->window.clear();
		_data->window.draw(_Background);
		_data->window.draw(_PlayButton);
		_data->window.draw(_QuitButton);
		_data->window.display();


	}
	void MainMenuState::init()
	{
		_data->assets.AddTexture("board", BOARD_PATH);
		_data->assets.AddTexture("figures", FIGURES_PATH);
		_data->assets.AddTexture("WhiteWon", WHITEWON_PATH);
		_data->assets.AddTexture("BlackWon", BLACKWON_PATH);
		Scaling::Set(_Background.getGlobalBounds().width, _Background.getGlobalBounds().height);
		Scaling::ScaleSprite(_Background);
		_QuitButton.scale(Bscale, Bscale);
		_PlayButton.scale(Bscale, Bscale);
		_QuitButton.setPosition(WindowWidth / 2, WindowHeight * 5 / 8);
		_PlayButton.setPosition(WindowWidth / 2, WindowHeight * 2 / 5);
		Scaling::ScaleSprite(_PlayButton);
		Scaling::ScaleSprite(_QuitButton);
		LoadNext();

	}
	void MainMenuState::loadnextstate()
	{
		nextstate = new GameState(_data);
	}
	void MainMenuState::resize()
	{
		_data->window.setView(sf::View(sf::FloatRect(0, 0, WindowWidth, WindowHeight)));
		Scaling::ScaleOnResize(_PlayButton);
		Scaling::ScaleOnResize(_QuitButton);
		Scaling::ScaleOnResize(_Background);
		Scaling::UpdateWindowSize();
	}
}