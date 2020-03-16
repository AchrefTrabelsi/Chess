#include "GameState.h"
namespace AT
{
	GameState::GameState(GameDataRef data) : _data(data), _figures(2)
	{
		Restart = false;
		cheat = 0;
		GameOverScreenSet = false;
		GameOver = false;
		board = new int* [8];
		for (int i = 0; i < 8; i++)
		{
			board[i] = new int[8];
		}
		checkmate = -1;
		focusedfigure=NULL;
		side = 1;
		mousecliked = false;
		_board.setTexture(_data->assets.GetTexture("board"));
		_figures[0].push_back(new Figure(_data, ROOK,0,0,0,board));
		_figures[0].push_back(new Figure(_data, KNIGHT, 0,1,0, board));
		_figures[0].push_back(new Figure(_data, BISHOP, 0, 2, 0, board));
		_figures[0].push_back(new Figure(_data, QUEEN, 0, 3, 0, board));
		_figures[0].push_back(new Figure(_data, KING, 0, 4, 0, board));
		_figures[0].push_back(new Figure(_data, BISHOP, 0, 5, 0, board));
		_figures[0].push_back(new Figure(_data, KNIGHT, 0, 6, 0, board));
		_figures[0].push_back(new Figure(_data, ROOK, 0, 7, 0, board));
		for (int i = 0; i < 8; i++)
		{
			_figures[0].push_back(new Figure(_data, PAWN, 0,i,1, board));
		}
		for (int i = 0; i < 8; i++)
		{
			_figures[1].push_back(new Figure(_data, PAWN, 1, i, 6, board));
		}

		_figures[1].push_back(new Figure(_data, ROOK, 1, 0, 7, board));
		_figures[1].push_back(new Figure(_data, KNIGHT, 1, 1, 7, board));
		_figures[1].push_back(new Figure(_data, BISHOP, 1, 2, 7, board));
		_figures[1].push_back(new Figure(_data, QUEEN, 1, 3, 7, board));
		_figures[1].push_back(new Figure(_data, KING, 1, 4, 7, board));
		_figures[1].push_back(new Figure(_data, BISHOP, 1, 5, 7, board));
		_figures[1].push_back(new Figure(_data, KNIGHT, 1, 6, 7, board));
		_figures[1].push_back(new Figure(_data, ROOK, 1, 7, 7, board));
		for (int i = 0; i < 8; i++)
		{
			board[0][i] = i+1;
		}
		for (int i = 0; i < 8; i++)
		{
			board[1][i] = i+8+1;
		}
		for (int j = 2; j < 6; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				board[j][i] = 0;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			board[6][i] = i+1+16 ;
		}
		for (int i = 0; i < 8; i++)
		{
			board[7][i] = i+ 1 + 8 +16;
		}



	}
	GameState::~GameState()
	{
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 16; i++)
			{
				if (_figures[j][i])
					delete _figures[j][i];
			}
		}
		for(int i=0 ; i<8; i++)
		{ 
			delete[] board[i];
		}
		delete[] board;
	}
	void GameState::HandleInput()
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
					mousecliked = true;
				}
				
			}
			else if (e.type == sf::Event::MouseButtonReleased)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					mousecliked = false;
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

			else if (e.type == sf::Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Return)
				{
					Restart = true;
				}
				else if (e.key.code == sf::Keyboard::W && cheat == 0)
				{
					cheat++;
				}
				else if (e.key.code == sf::Keyboard::I && cheat == 1)
				{
					cheat++;
				}
				else if (e.key.code == sf::Keyboard::N && cheat == 2)
				{
					cheat++;
				}
				else if (e.key.code == sf::Keyboard::W && cheat == 3)
				{
					cheat++;
				}
				else if (e.key.code == sf::Keyboard::B && cheat == 3)
				{
					cheat+=2;
				}
				else
				{
					cheat = 0;
				}

			}
		}
	}
	void GameState::Update(float dt)
	{
		if (Restart && GameOver)
		{
			nextstateloader.join();
			_data->machine.AddState(StateRef(nextstate));
		}

		if (cheat == 4 && !GameOver)
		{
			GameOver = true;
			side = 0;
		}
		if (cheat == 5 && !GameOver)
		{
			GameOver = true;
			side = 1;
		}
		if (!GameOver)
		{

			sf::Vector2i mousepos = _data->input.MousePosition(_data->window);
			if (mousecliked && mousepos.x < WindowWidth && mousepos.y < WindowHeight && mousepos.x>0 && mousepos.y>0)
			{
				sf::Vector2i pos = ToBoardCoord(mousepos);

				if (focusedfigure == NULL)
				{
					originalpos = pos;
					int x = board[pos.y][pos.x] - 1;
					if (x != -1)
					{
						if (x > 15 && side)
						{
							focusedfigure = _figures[1][x - 16];
						}
						else if (x < 16 && side == 0)
						{
							focusedfigure = _figures[0][x];
						}
					}
				}
				if (focusedfigure)
				{
					focusedfigure->move(mousepos);
				}

			}
			else if (!mousecliked)
			{
				if (focusedfigure) // on mouse realease do
				{
					if (focusedfigure->update())
					{
						sf::Vector2i pos = ToBoardCoord(mousepos);
						sf::Vector2i oldpos;
						if (Figure::castle)
						{
							Figure::castle = false;
							if (pos.x == 2)
							{
								oldpos.x = 0;
								oldpos.y = 7 * side;
								_figures[side][0 + 8 * side]->forcesetposition(sf::Vector2i(3, 7 * side));

							}
							if (pos.x == 6)
							{
								oldpos.x = 7;
								oldpos.y = 7 * side;
								_figures[side][7 + 8 * side]->forcesetposition(sf::Vector2i(5, 7 * side));

							}

							checkmate = check();
							if (checkmate == side)
							{
								if (pos.x == 2)
								{
									_figures[side][0 + 8 * side]->forcesetposition(oldpos);

								}
								if (pos.x == 6)
								{
									_figures[side][7 + 8 * side]->forcesetposition(oldpos);

								}
								checkmate = -1;
								focusedfigure->forcesetposition(originalpos);

							}
							else
							{
								Figure::cancastle[side][0] = false;
								Figure::cancastle[side][1] = false;
								if (pos.x == 2)
								{
									board[7 * side][3] = board[7 * side][0];
									board[7 * side][0] = 0;

								}
								if (pos.x == 6)
								{
									board[7 * side][5] = board[7 * side][7];
									board[7 * side][7] = 0;

								}
								board[pos.y][pos.x] = board[originalpos.y][originalpos.x];
								board[originalpos.y][originalpos.x] = 0;
								side = (side + 1) % 2;


							}


						}
						else
						{
							Figure* tempfig = NULL;
							sf::Vector2i pos = focusedfigure->getposition();
							int x = board[pos.y][pos.x] - 1;
							if (x != -1)
							{
								if (x > 15)
								{
									tempfig = _figures[1][x - 16];
									_figures[1][x - 16] = NULL;
								}
								else
								{
									tempfig = _figures[0][x];
									_figures[0][x] = NULL;
								}
							}
							int temp = board[pos.y][pos.x];
							board[pos.y][pos.x] = board[originalpos.y][originalpos.x];
							board[originalpos.y][originalpos.x] = 0;

							checkmate = check();
							if (checkmate == side)
							{
								focusedfigure->forcesetposition(originalpos);
								if (x != -1)
								{
									if (x > 15)
									{
										_figures[1][x - 16] = tempfig;
									}
									else
									{
										_figures[0][x] = tempfig;
									}
								}
								board[originalpos.y][originalpos.x] = board[pos.y][pos.x];
								board[pos.y][pos.x] = temp;




								checkmate = -1;
							}
							else
							{
								if (focusedfigure->gettype() == KING)
								{
									Figure::cancastle[side][0] = false;
									Figure::cancastle[side][1] = false;
								}
								if (focusedfigure->gettype() == ROOK)
								{
									if (originalpos.x == 0)
									{
										Figure::cancastle[side][0] = false;
									}
									if (originalpos.x == 7)
									{
										Figure::cancastle[side][1] = false;
									}

								}
								if (tempfig)
									delete tempfig;

								side = (side + 1) % 2;
							}
						}
					}
					focusedfigure = NULL;
					GameOver = gameover();
				}
			}
		}

	}
	void GameState::Draw()
	{
		if (!GameOverScreenSet)
		{
			_data->window.clear();
			_data->window.draw(_board);
			for (int i = 0; i < _figures[0].size(); i++)
			{
				if (_figures[0][i] != NULL && _figures[0][i] != focusedfigure)
					_figures[0][i]->draw();
			}
			for (int i = 0; i < _figures[1].size(); i++)
			{
				if (_figures[1][i] != NULL && _figures[1][i] != focusedfigure)
					_figures[1][i]->draw();
			}
			if (focusedfigure != NULL)
				focusedfigure->draw();


			if (GameOver)
			{
				sf::Sprite gameoverscreen;
				if (side == 0)
				{
					gameoverscreen.setTexture(_data->assets.GetTexture("WhiteWon"));
				}
				else
				{
					gameoverscreen.setTexture(_data->assets.GetTexture("BlackWon"));
				}
				gameoverscreen.setOrigin(gameoverscreen.getGlobalBounds().width / 2, gameoverscreen.getGlobalBounds().height / 2);
				gameoverscreen.setPosition(WindowWidth / 2, WindowHeight / 2);
				_data->window.draw(gameoverscreen);
				_data->window.display();
				GameOverScreenSet = true;
			}
			else
			{
				_data->window.display();

			}
		}

	}
	void GameState::init()
	{
		Scaling::Set(_board.getGlobalBounds().width, _board.getGlobalBounds().height);
		Scaling::ScaleSprite(_board);
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 16; j++)
				_figures[i][j]->init();
		LoadNext();
	}
	int GameState::check()
	{
		sf::Vector2i kingpos;
		int oside = (side + 1) % 2;
		kingpos = _figures[side][4+8*side]->getposition();
		for (int i = 0; i < 16; i++)
		{
			if(_figures[oside][i]!=NULL)
				if (_figures[oside][i]->possiblemove(kingpos))
				{
					return side;
				}
		}
		return -1;
	}
	bool GameState::gameover()
	{
		checkmate = check();
		if (side==checkmate)
		{
			sf::Vector2i kingpos;
			std::vector<Figure*> figures;
			int oside = (side + 1) % 2;
			kingpos = _figures[side][4+8*side]->getposition();
			for (int i = 0; i < 16; i++)
			{
				if (_figures[oside][i] != NULL)
					if (_figures[oside][i]->possiblemove(kingpos))
					{
						figures.push_back(_figures[oside][i]);
					}
			}
			if (figures.size() < 2 )
			{
				sf::Vector2i position = figures[0]->getposition();
				for (int i = 0; i < 16; i++)
				{
					if (_figures[side][i] != NULL)
					{
						if (checkmove(position, _figures[side][i]))
						{
							return false;
						}
					}
				}
				sf::Vector2i dir =figures[0]->direction(kingpos-position);
				if (dir.x != 0 || dir.y != 0)
				{
					position += dir;
					while (position!=kingpos)
					{
						for (int i = 0; i < 16; i++)
						{
							if(_figures[side][i])
								if (checkmove(position, _figures[side][i]))
								{
									return false;
								}
						}
						position += dir;
					}
				}
			}
			sf::Vector2i move(1,1) ;
			while (move.y>-2)
			{
				move.x = 1;
				if (checkmove(move + kingpos, _figures[side][4 + 8 * side]))
				{
					return false;
				}
				move.x = 0;
				if (checkmove(move + kingpos, _figures[side][4 + 8 * side]))
				{
					return false;
				}
				move.x = -1;
				if (checkmove(move + kingpos, _figures[side][4 + 8 * side]))
				{
					return false;
				}
				move.y--;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	bool GameState::checkmove(sf::Vector2i move, Figure* figure)
	{
		if (move.x > 7 || move.y > 7 || move.x < 0 || move.y < 0)
		{
			return false;
		}
		sf::Vector2i oldpos = figure->getposition();
		int chkmate = -1;
		sf::Vector2f scale = Scaling::GetScale();
		move.x = move.x * (BoardSquare*scale.x);
		move.y = move.y * (BoardSquare*scale.y);
		figure->move(move);
		if (figure->update())
		{
			Figure* tempfig = NULL;
			sf::Vector2i pos = figure->getposition();
			int x = board[pos.y][pos.x] - 1;
			if (x != -1)
			{
				if (x > 15)
				{
					tempfig = _figures[1][x - 16];
					_figures[1][x - 16] = NULL;
				}
				else
				{
					tempfig = _figures[0][x];
					_figures[0][x] = NULL;
				}
			}
			int temp = board[pos.y][pos.x];
			board[pos.y][pos.x] = board[oldpos.y][oldpos.x];
			board[oldpos.y][oldpos.x] = 0;
			chkmate = check();
			figure->forcesetposition(oldpos);
			if (x != -1)
			{
				if (x > 15)
				{
					_figures[1][x - 16] = tempfig;
				}
				else
				{
					_figures[0][x] = tempfig;
				}
			}
			board[oldpos.y][oldpos.x] = board[pos.y][pos.x];
			board[pos.y][pos.x] = temp;
			if (chkmate != side)
				return true;

		}
 		return false;
	}
	void GameState::loadnextstate()
	{
		nextstate = new GameState(_data);
	}
	void GameState::resize()
	{
		_data->window.setView(sf::View(sf::FloatRect(0, 0, WindowWidth, WindowHeight)));
		Scaling::ScaleOnResize(_board);
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 16; j++)
				_figures[i][j]->resize();
		Scaling::UpdateWindowSize();
	}
}

