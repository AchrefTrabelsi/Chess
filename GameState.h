#pragma once
#include "Game.h"
#include "State.h"
#include "Figure.h"
#include <thread>
namespace AT
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		~GameState();
		void HandleInput() ;
		void Update(float dt) ;
		void Draw() ;
		void init();
		int check();
		bool gameover();
		bool checkmove(sf::Vector2i move, Figure* figure);
		void loadnextstate();
		void resize();


	private:
		GameDataRef _data;
		sf::Sprite _board;
		std::vector<std::vector<Figure*>> _figures;
		int **board;
		Figure*  focusedfigure;
		bool mousecliked;
		int cheat;
		int side;
		sf::Vector2i originalpos;
		int checkmate;
		bool GameOver;
		bool GameOverScreenSet;
		bool Restart;
	};

}