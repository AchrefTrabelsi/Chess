#pragma once
#include "Game.h"
#include "Definitions.h"
namespace AT
{
	class Figure
	{
	public:
		static bool cancastle[2][2] ;
		static bool castle;
		Figure(GameDataRef data , int type, int side,int posx,int posy,int ** board);
		bool update();
		void move(sf::Vector2i pos);
		void position();
		void draw();
		void resize();
		void init();
		void forcesetposition(sf::Vector2i pos);
		sf::Vector2i direction(sf::Vector2i dir);
		bool possiblemove(sf::Vector2i pos);
		sf::Vector2i getposition();
		int gettype();

	private:
		void setposition(sf::Vector2i pos);
		int _Type;
		sf::Sprite _figure;
		sf::Vector2i originalpos;
		sf::Vector2i newpos;
		GameDataRef _data;
		int** _board;
		int _side;

	};
}
