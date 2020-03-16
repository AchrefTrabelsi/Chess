#include "Figure.h"
namespace AT
{
	bool Figure::castle = false;
	bool Figure::cancastle[2][2] = {true,true,true,true};
	static int const size  = 56;
	Figure::Figure(GameDataRef data, int type,int side,int posx , int posy,int ** board) : _data(data) , _Type(type)
	{
		_side = side;
		_board = board;
		_figure.setTexture(_data->assets.GetTexture("figures"));
		_figure.setTextureRect(sf::IntRect(size*type, size*side,size,size));
		originalpos = sf::Vector2i(posx,posy);
		newpos = originalpos;
	}
	void Figure::move(sf::Vector2i pos)
	{
		sf::Vector2f scale = Scaling::GetScale();
		_figure.setPosition(pos.x-(BoardSquare*scale.x)/2, pos.y-(BoardSquare*scale.y)/2);
	}
	void Figure::position()
	{
		sf::Vector2f scale = Scaling::GetScale();
		sf::Vector2i pos(0,0) ;
		pos.x = BoardSquare * scale.x/ 2 + _figure.getPosition().x;
		pos.y += BoardSquare * scale.y / 2 + _figure.getPosition().y;
		newpos = ToBoardCoord(pos);
	}
	void Figure::setposition(sf::Vector2i pos)
	{
		sf::Vector2f scale = Scaling::GetScale();
		_figure.setPosition(size * pos.x * scale.x + 4, size * pos.y * scale.y + 2);
	}
	void Figure::draw()
	{
		_data->window.draw(_figure);
	}
	void Figure::resize()
	{
		Scaling::ScaleOnResize(_figure);
	}
	void Figure::init()
	{
		sf::Vector2f scale = Scaling::GetScale();
		_figure.setPosition(BoardSquare * originalpos.x * scale.x + 4, BoardSquare * originalpos.y * scale.y + 2);
		Scaling::ScaleSprite(_figure);
	}
	void Figure::forcesetposition(sf::Vector2i pos)
	{
		originalpos = pos;
		newpos = pos;
		setposition(pos);
	}
	sf::Vector2i Figure::direction(sf::Vector2i dir)
	{
		int distance;
		if (dir.x == 0 && dir.y == 0)
			return sf::Vector2i(0, 0);
		if (_Type == BISHOP)
		{
			if (dir.x != 0 && dir.y != 0)
			{
				if (dir.x / dir.y == 1 || dir.x / dir.y == -1)
				{
					distance = abs(dir.x);
					return sf::Vector2i(dir.x /distance , dir.y / distance);
				}
			}
		}
		else if (_Type == ROOK)
		{
			if (dir.x == 0)
			{
				distance = abs(dir.y);
				return sf::Vector2i(0, dir.y / distance );
			}
			if (dir.y == 0)
			{
				distance = abs(dir.x);
				return sf::Vector2i(dir.x / distance,0 );
			}

		}

		else if (_Type == QUEEN)
		{
			if (dir.x == 0)
			{
				distance = abs(dir.y);
				return sf::Vector2i(0, dir.y / distance);
			}
			if (dir.y == 0)
			{
				distance = abs(dir.x);
				return sf::Vector2i(dir.x / distance, 0);
			}
			if (dir.x / dir.y == 1 || dir.x / dir.y == -1)
			{
				distance = abs(dir.x);
				return sf::Vector2i(dir.x / distance, dir.y / distance);
			}
		}
		return sf::Vector2i(0, 0);
	}
	bool Figure::possiblemove(sf::Vector2i pos)
	{
		if (pos == originalpos )
			return false;
		sf::Vector2i dir;
		int destination = _board[pos.y][pos.x];
		dir = pos - originalpos;
		if (_Type == KNIGHT)
		{
			if (dir.x * dir.y != 2 && dir.x * dir.y != -2)			
				return false;
		}
		else if (_Type == PAWN)
		{
			if (originalpos.y == 6 && _side == 1 && dir.y == -2 && dir.x == 0 && destination == 0)
				return true;
			else if (originalpos.y == 1 && _side == 0 && dir.y == 2 && dir.x == 0 && destination == 0)
				return true;
			else if ((_side && dir.y == -1)|| (_side == 0 && dir.y == 1))
			{
				if ((dir.x == 0 && destination==0)|| (abs(dir.x) == 1 && destination));
				else
					return false;
			}
			else
			{
				return false;
			}
		}
		else if (_Type == KING)
		{
			if (pos.x == 2 && pos.y == 7 * _side && cancastle[_side][0])
			{
				if (_board[_side * 7][1]==0 && _board[_side * 7][2] == 0 && _board[_side * 7][3]== 0)
				{
					castle = true;
					return true;
				}
			}
			if (pos.x == 6 && pos.y == 7 * _side && cancastle[_side][1])
			{
				if (_board[_side * 7][5] == 0 && _board[_side * 7][6]== 0)
				{
					castle = true;
					return true;
				}
			}

			if (abs(dir.x) > 1 || abs(dir.y) > 1)
				return false;
		}
		else
		{
			dir = direction(dir);
			if (dir.x == 0 && dir.y == 0)
				return false;
			sf::Vector2i temppos;
			temppos = originalpos + dir;
			while (_board[temppos.y][temppos.x] == 0)
			{
				if (temppos == pos)
					break;
				temppos += dir;
			}
			if (temppos != pos)
			{
				return false;
			}
		}
		if (destination == 0)
			return true;
		else if (_side != destination / 17)
			return true;
		else
			return false;

	}
	sf::Vector2i Figure::getposition()
	{
		return originalpos;
	}
	int Figure::gettype()
	{
		return _Type;
	}
	bool Figure::update()
	{
		position();
		bool changed = false;
		if (possiblemove(newpos))
		{
			changed = true;
			originalpos = newpos;
		}
		else
		{
			newpos = originalpos;
		}
		setposition(originalpos);
		return changed;
	}
}