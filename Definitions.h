#pragma once
#include <SFML/Graphics.hpp>
#define FPS 60.0f
#define BoardSquare (454/8)
#define SPLASH_TIME 2.5
#define ICON_PATH "resources/icon.png"
#define WHITEWON_PATH "resources/WhiteWon.png"
#define BLACKWON_PATH "resources/BlackWon.png"
#define LOGO_PATH "resources/logo.png"
#define BOARD_PATH "resources/board0.png"
#define FIGURES_PATH "resources/figures.png"
#define MAIN_MENU_BACKGROUND_PATH "resources/smainmenubg.jpg"
#define PLAY_BUTTON_PATH "resources/PlayButton.png"
#define PLAY_BUTTON_HOVER_PATH "resources/PlayButtonHover.png"
#define PLAY_BUTTON_CLICKED_PATH "resources/PlayButtonClicked.png"
#define QUIT_BUTTON_PATH "resources/QuitButton.png"
#define QUIT_BUTTON_HOVER_PATH "resources/QuitButtonHover.png"
#define QUIT_BUTTON_CLICKED_PATH "resources/QuitButtonClicked.png"
#define PAWN 5
#define BISHOP 2
#define QUEEN 3
#define KNIGHT 1
#define ROOK 0
#define KING 4

#include <iostream>



//---------------------Functions---------------------//

namespace AT
{
	extern int WindowHeight;
	extern int WindowWidth;
	namespace Scaling
	{
		void ScaleSprite(sf::Sprite& sprite);
		void ScaleSpriteWithoutDeforming(sf::Sprite& sprite);
		void Set(float heigt, float width);
		float GetScalef();
		sf::Vector2f GetScale();
		void ScaleOnResize(sf::Sprite& sprite);
		void UpdateWindowSize();

	}
	sf::Vector2i ToBoardCoord(sf::Vector2i pos);

}