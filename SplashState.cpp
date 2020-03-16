#include "SplashState.h"
#include "MainMenuState.h"
namespace AT
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{
		_data->assets.AddTexture("bg", LOGO_PATH);
		_background.setTexture(_data->assets.GetTexture("bg"));
		//_background.setScale(0.1, 0.1);
		_background.setPosition(WindowWidth/2 - _background.getGlobalBounds().width / 2, WindowHeight/2 - _background.getGlobalBounds().height / 2);
	}
	SplashState::~SplashState()
	{

	}
	void SplashState::HandleInput()
	{
		sf::Event e;
		while (_data->window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				_data->window.close();
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
				_data->window.setView(sf::View(sf::FloatRect(0, 0, WindowWidth, WindowHeight)));
				Scaling::ScaleOnResize(_background);
				Scaling::UpdateWindowSize();
			}
		}
	}
	void SplashState::Update(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > SPLASH_TIME)
		{
			if (nextstate!=NULL)
			{
				nextstateloader.join();
				_data->machine.AddState(StateRef(nextstate));
				nextstate = NULL;
			}
		}
	}
	void SplashState::Draw()
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.display();
	}
	void SplashState::init()
	{
		_data->assets.AddTexture("Background", MAIN_MENU_BACKGROUND_PATH);
		_data->assets.AddTexture("PlayButton", PLAY_BUTTON_PATH);
		_data->assets.AddTexture("PlayButtonHover", PLAY_BUTTON_HOVER_PATH);
		_data->assets.AddTexture("PlayButtonClicked", PLAY_BUTTON_CLICKED_PATH);
		_data->assets.AddTexture("QuitButton", QUIT_BUTTON_PATH);
		_data->assets.AddTexture("QuitButtonHover", QUIT_BUTTON_HOVER_PATH);
		_data->assets.AddTexture("QuitButtonClicked", QUIT_BUTTON_CLICKED_PATH);
		LoadNext();

	}
	void SplashState::loadnextstate()
	{
		nextstate = new MainMenuState(_data);
	}
}
