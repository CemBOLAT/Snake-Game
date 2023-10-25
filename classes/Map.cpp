#include "../includes/Map.hpp"
#include "../includes/Defines.h"
#include "../includes/Game.hpp"

Map::Map(void)
{
	this->_map = new char*[HEIGHT / SIZE];

	for (int i = 0; i < HEIGHT / SIZE; i++)
	{
		this->_map[i] = new char[WIDTH / SIZE];
		for (int j = 0; j < WIDTH / SIZE; j++)
		{
			if (i == 0 || i == HEIGHT / SIZE - 1 || j == 0 || j == WIDTH / SIZE - 1)
				this->_map[i][j] = BOUNDARY;
			else
				this->_map[i][j] = BACKGROUND;
		}
	}
}

Map::Map(Map const & src)
{
	*this = src;
}

Map::~Map(void)
{
	for (int i = 0; i < HEIGHT / SIZE; i++)
	{
		delete [] this->_map[i];
	}
	delete [] this->_map;
}

Map	&Map::operator=(Map const & copy)
{
	if (this != &copy)
	{
		for (int i = 0; i < HEIGHT / SIZE; i++)
		{
			delete [] this->_map[i];
		}
		delete [] this->_map;
		this->_map = new char*[HEIGHT / SIZE];
		for (int i = 0; i < HEIGHT / SIZE; i++)
		{
			this->_map[i] = new char[WIDTH / SIZE];
			for (int j = 0; j < WIDTH / SIZE; j++)
			{
				this->_map[i][j] = copy._map[i][j];
			}
		}
	}
	return (*this);
}

char	Map::getMapElement(int x, int y) const
{
	return (this->_map[y][x]);
}

void	Map::setMapElement(int x, int y, char c)
{
	this->_map[y][x] = c;
}

void Map::printMap(sf::RenderWindow &window, sf::Sprite backgroundSprite, sf::Sprite foodSprite, sf::Sprite obstacleSprite, sf::Sprite playerSprite, sf::Sprite bodySprite, sf::Sprite boundarySprite) {
	for (int i = 0; i < HEIGHT / SIZE; i++) {
		for (int j = 0; j < WIDTH / SIZE; j++) {
			sf::Vector2f position(j * SIZE, i * SIZE);

			if (this->_map[i][j] == BACKGROUND){
				backgroundSprite.setPosition(position);
				window.draw(backgroundSprite);
			}
			else if (this->_map[i][j] == FOOD) {
				foodSprite.setPosition(position);
				window.draw(foodSprite);
			}
			else if (this->_map[i][j] == OBSTACLE) {
				obstacleSprite.setPosition(position);
				window.draw(obstacleSprite);
			}
			else if (this->_map[i][j] == PLAYER) {
				playerSprite.setPosition(position);
				window.draw(playerSprite);
			}
			else if (this->_map[i][j] == BODY) {
				bodySprite.setPosition(position);
				window.draw(bodySprite);
			}
			else if (this->_map[i][j] == BOUNDARY) {
				boundarySprite.setPosition(position);
				window.draw(boundarySprite);
			}
		}
	}
}


void	Map::deleteAllMapElements(void)
{
	for (int i = 0; i < HEIGHT / SIZE; i++)
	{
		for (int j = 0; j < WIDTH / SIZE; j++)
		{
			if (this->_map[i][j] != FOOD && this->_map[i][j] != OBSTACLE && this->_map[i][j] != BOUNDARY)
				this->_map[i][j] = BACKGROUND;
		}
	}
}

void	Map::clearMap(void)
{
	for (int i = 0; i < HEIGHT / SIZE; i++)
	{
		for (int j = 0; j < WIDTH / SIZE; j++)
		{
			if (this->_map[i][j] != BOUNDARY)
				this->_map[i][j] = BACKGROUND;
		}
	}
}
