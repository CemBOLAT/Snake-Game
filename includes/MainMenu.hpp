#pragma once

#include "Defines.h"
#include "Texture.hpp"
#include "Game.hpp"

class Game;

using namespace std;

class MainMenu
{
	private:
		sf::Text		titleText;
		sf::Text		namePrompt;
		sf::Text		playerName;
		sf::Text		startText;
		sf::Text		tutorialText;
		sf::Text		leaderboardText;
		sf::Text		exitText;
		sf::Font		font;
		std::string		selectedText;

	public:
		MainMenu(void);
		MainMenu(MainMenu const & src);
		~MainMenu(void);

		sf::Text		getTitleText(void) const;
		sf::Text		getNamePrompt(void) const;
		sf::Text		getPlayerName(void) const;
		sf::Text		getStartText(void) const;
		sf::Text		getTutorialText(void) const;
		sf::Text		getLeaderboardText(void) const;
		sf::Text		getExitText(void) const;


		sf::Text		setPlayerName(string name);
		void			draw(sf::RenderWindow &window);
		void			select(string playerNameString, Game &gameObjec);
		void			downArrow();
		void			upArrow();
};
