#include "../includes/Snake.hpp"
#include "../includes/Defines.h"
#include <iostream>

Snake::Snake(void)
{
	this->x = 0;
	this->y = 0;
	this->direction = 111;
}

Snake::Snake(Snake const & src)
{
	*this = src;
}

Snake::~Snake(void){}

Snake	&Snake::operator=(Snake const & copy)
{
	if (this != &copy)
	{
		this->x = copy.x;
		this->y = copy.y;
		this->direction = copy.direction;
	}
	return (*this);
}

int		Snake::getX(void) const
{
	return (this->x);
}

int		Snake::getY(void) const
{
	return (this->y);
}

int		Snake::getDirection(void) const
{
	return (this->direction);
}

void	Snake::setX(int x)
{
	this->x = x;
}

void	Snake::setY(int y)
{
	this->y = y;
}

void	Snake::setDirection(int direction)
{
	this->direction = direction;
}

void	Snake::move(void)
{
	if (this->direction == RIGHT)
		this->x++;
	else if (this->direction == LEFT)
		this->x--;
	else if (this->direction == UP)
		this->y--;
	else if (this->direction == DOWN)
		this->y++;
};
