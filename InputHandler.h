#pragma once
#include <SFML\Graphics.hpp>
namespace AT
{
	class InputHandler
	{
	public:
		bool isSpriteClicked(sf::Sprite& sprite,sf::Mouse::Button mbutton,sf::RenderWindow &window);
		sf::Vector2i MousePosition(sf::RenderWindow &window );
	};

}