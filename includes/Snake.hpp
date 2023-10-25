#pragma once

class Snake{
	private :
		int		x;
		int		y;
		int		direction;
	public :
		Snake(void);
		Snake(Snake const & src);
		~Snake(void);
		Snake & operator=(Snake const & copy);

		int	getX(void) const;
		int	getY(void) const;
		int	getDirection(void) const;

		void	setX(int x);
		void	setY(int y);
		void	setDirection(int direction);

		void	move(void);
};
