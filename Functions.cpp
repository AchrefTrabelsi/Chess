#include "Definitions.h"
namespace AT
{
	static int OldWindowHeight = 600;
	static int OldWindowWidth = 600;
	int WindowHeight = 600;
	int WindowWidth = 600;
	namespace Scaling
	{
		static float Width, Height,Scalef;
		static sf::Vector2f Scale;
		void ScaleSprite(sf::Sprite& sprite)
		{
			sprite.scale(Scale);
		}
		void ScaleSpriteWithoutDeforming(sf::Sprite& sprite)
		{
			sprite.scale(Scalef, Scalef);
		}
		void Set(float width, float height)
		{
			Width = width;
			Height = height;			
			Scale.x = WindowWidth / Width;
			Scale.y = WindowHeight / Height;
			Scalef = fminf(Scale.x, Scale.y);

		}
		float GetScalef()
		{
			return Scalef;
		}

		sf::Vector2f GetScale()
		{
			return Scale;
		}
		void ScaleOnResize(sf::Sprite& sprite)
		{
			sf::Vector2f pos = sprite.getPosition();
			float hscale = (float)WindowHeight / OldWindowHeight;
			float wscale = (float)WindowWidth/ OldWindowWidth;
			sprite.setPosition(pos.x*wscale,pos.y* hscale);
			sprite.scale(wscale, hscale);
		}
		void UpdateWindowSize()
		{
			float hscale = WindowHeight / OldWindowHeight;
			float wscale = WindowWidth / OldWindowWidth;
			OldWindowHeight = WindowHeight;
			OldWindowWidth = WindowWidth;
			Scale.x = WindowWidth / Width;
			Scale.y = WindowHeight / Height;
			Scalef = fminf(Scale.x, Scale.y);
		}

	}
	sf::Vector2i ToBoardCoord(sf::Vector2i pos)
	{
		sf::Vector2f scale = Scaling::GetScale();
		int x = scale.x * BoardSquare;
		int y = scale.y * BoardSquare;
		x = pos.x / x;
		y = pos.y / y;
		while (x>7)
		{
			x--;
		}
		while (y>7)
		{
			y--;
		}
		return sf::Vector2i(x , y);
	}

}