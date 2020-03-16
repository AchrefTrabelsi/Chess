#pragma once
#include <SFML\Graphics.hpp>
#include <map>
namespace AT
{
	class AssetManager
	{
	public:
		void AddTexture(std::string name, std::string filepath);
		sf::Texture& GetTexture(std::string name);
		void AddFont(std::string name, std::string filepath);
		sf::Font& GetFont(std::string name);

	private:
		std::map<std::string, sf::Texture> _Textures;
		std::map<std::string, sf::Font> _Fonts;

	};
}
