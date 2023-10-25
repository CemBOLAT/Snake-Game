#pragma once

#include <iostream>
using namespace std;

#ifndef LEADERBOAD_TEXT_NAME
# define LEADERBOAD_TEXT_NAME "./asset/base/leaderboard.txt"
#endif

#include <utility>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class LeaderBoard{
	private :
		sf::Font			_font;
		sf::Text			exitText;
		sf::Text			menuText;
		sf::Text			infoText;
		int					_playerNum;
		pair<string, int>	*_player;
		pair<string, int>	*allPlayers;
		pair<int, int> 		*allTime;
	public :
		LeaderBoard(void);
		~LeaderBoard(void);

		int		getPlayerNum(void) const;
		void	setPlayerNum(int playerNum);
		void	initPlayerNum(void);
		void	readAndFill(void);
		pair<string, int>	*getAllPlayers(void) const;
		pair<string, int>	*getPlayer(void) const;
		pair<int, int>		*getAllTime(void) const;

		void	delAllPlayers(void);
		void	delAllTime(void);
		void	delPlayer(void);

		void	setAllPlayers(pair<string, int> *allPlayers);
		void	setPlayer(pair<string, int> *player);
		void	setAllTime(pair<int, int> *allTime);

		sf::Text	getExitText(void) const;
		sf::Text	getMenuText(void) const;
		sf::Text	getInfoText(void) const;
};

