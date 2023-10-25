#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using std::string;

class Map{
	private :
		char		**_map;
	public :
		Map(void);
		Map(Map const & src);
		~Map(void);
		Map & operator=(Map const & copy);

		char	getMapElement(int x, int y) const;
		void	setMapElement(int x, int y, char c);
		void	printMap(sf::RenderWindow &window, sf::Sprite backgroundSprite,
							sf::Sprite foodSprite, sf::Sprite obstacleSprite,
							sf::Sprite playerSprite, sf::Sprite bodySprite,
							sf::Sprite boundarySprite);
		void	deleteAllMapElements(void);
		void	clearMap(void);

};
