#pragma once

#include <iostream>
#include "Defines.h"
#include "Map.hpp"
#include "Snake.hpp"
#include "Texture.hpp"
#include "MainMenu.hpp"
#include "LeaderBoard.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class MainMenu;
class GameOver;

using std::string;

class Game{
	private :
		const sf::Time		TIME_PER_FRAME = sf::seconds(1.f / 60.f);
		int					_score;
		int					_snakeSize;
		bool				_gameOver;
		string				_name;
		Map					_map;
		Snake				*_snake;
		Texture				_texture;
		MainMenu			*_mainMenu;
		GameOver			*_gameOverMenu;
		sf::Clock			_timer;
		sf::RenderWindow	window;
		LeaderBoard			_leaderBoard;
	public :
		Game(void);
		Game(Game const & src);
		~Game(void);
		Game & operator=(Game const & copy);

		string	getName(void) const;
		void	setName(string name);
		void	setSnakeSize(int size);
		int		getSnakeSize(void) const;
		void	setScore(int score);
		int		getScore(void) const;
		void	setGameOver(bool gameOver);
		bool	getGameOver(void) const;

		void	start(void);
		void	run(void);

		void	createRandomBlock(char type);
		void	createRandomBlock(char type, int x, int y);

		sf::Keyboard::Key	getInput(sf::RenderWindow &window);
		void				moveSnake(string input);
		int					getDirections(int &x, int &y, string input);

		void				iterateSnake(int x_dir, int y_dir);
		void				checkCollision(void);
		void				addSnakeToMap(void);
		void				mainMenu(void);
		void				tutorial(void);
		void				resetGame();
		void				gameOverMenu(sf::Time elapsedTime);
		void				useInput(sf::Keyboard::Key input);

		void				draw(sf::RenderWindow &window);
		void				setLeaderBoard(string name, int score);
		void				getLeaderBoardScene(void);
};
