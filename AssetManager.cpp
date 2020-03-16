#include "AssetManager.h"
namespace AT
{
	void AssetManager::AddTexture(std::string name, std::string filepath)
	{
		sf::Texture tex;
		if (tex.loadFromFile(filepath))
		{
			_Textures[name] = tex;
		}
	}

	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return _Textures[name];
	}

	void AssetManager::AddFont(std::string name, std::string filepath)
	{
		sf::Font ft;
		if (ft.loadFromFile(filepath))
		{
			_Fonts[name] = ft;
		}

	}

	sf::Font& AssetManager::GetFont(std::string name)
	{
		return _Fonts[name];
	}
}