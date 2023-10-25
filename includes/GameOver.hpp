#pragma once

#include "Defines.h"
#include "Texture.hpp"
#include "Game.hpp"

class GameOver{
	private :
		sf::Text		gameOverText;
		sf::Text		scoreText;
		sf::Text		timeText;
		sf::Text		restartText;
		sf::Text		saveText;
		sf::Text		exitText;
		sf::Font		font;
		std::string		name;
		int				score;
		std::string		selectedText;
		sf::Time		_elapsedTime;
		bool			exit_game;
	public :
		GameOver(void);
		GameOver(GameOver const & src);
		~GameOver(void);

		sf::Text		getGameOverText(void) const;
		sf::Text		getScoreStr(void) const;
		sf::Text		getTimeText(void) const;
		sf::Text		getRestartText(void) const;
		sf::Text		getSaveText(void) const;
		sf::Text		getExitText(void) const;
		std::string		getSelectedText(void) const;
		bool			getExitGame(void) const;
		
		void			setExitGame(bool exit);
		void			setSelectedText(std::string text);
		void			setProperties(string name, int score, sf::Time elapsedTime);
		void			draw(sf::RenderWindow &window);
		void			select(string playerNameString, Game &gameObjec);
		void			downArrow();
		void			upArrow();
};
