#include "../includes/Game.hpp"
#include "../includes/Defines.h"
#include "../includes/Snake.hpp"
#include "../includes/Map.hpp"
#include "../includes/Texture.hpp"
#include "../includes/MainMenu.hpp"
#include "../includes/GameOver.hpp"

using namespace std;

Game::Game(void) : _score(0), _snakeSize(1), _gameOver(false), _name("Default"), _map(), _texture() /*, _leaderBoard()*/
{
	this->_snake = new Snake[this->_snakeSize];
	this->_mainMenu = new MainMenu();
	this->_gameOverMenu = new GameOver();
}

Game::Game(Game const & src)
{
	*this = src;
}

Game::~Game(void){
	delete this->_mainMenu;
	delete this->_gameOverMenu;
	delete [] this->_snake;
}

Game	&Game::operator=(Game const & copy)
{
	if (this != &copy)
	{
		delete [] this->_snake;
		this->_snake = new Snake[copy._snakeSize];
		for (int i = 0; i < copy._snakeSize; i++)
		{
			this->_snake[i] = copy._snake[i];
		}
		this->_map = copy._map;
		this->_score = copy._score;
		this->_snakeSize = copy._snakeSize;
	}
	return (*this);
}

void	Game::start(void)
{
	this->createRandomBlock(PLAYER);
	this->createRandomBlock(FOOD);
	this->createRandomBlock(OBSTACLE);
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Snake Game");
	this->mainMenu();
}

void	Game::createRandomBlock(char type)
{
	int		x;
	int		y;

	srand(time(NULL));

	do {
		x = rand() % (WIDTH / SIZE);
		y = rand() % (HEIGHT / SIZE);
	} while (this->_map.getMapElement(x, y) != BACKGROUND);
	if (type == PLAYER){
		this->_snake->setY(y);
		this->_snake->setX(x);
	}
	this->_map.setMapElement(x, y, type);
}

void	Game::createRandomBlock(char type, int x, int y)
{
	this->_map.setMapElement(x, y, type);
}

sf::Keyboard::Key Game::getInput(sf::RenderWindow &window){
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		return (sf::Keyboard::W);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		return (sf::Keyboard::S);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		return (sf::Keyboard::A);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		return (sf::Keyboard::D);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return (sf::Keyboard::Escape);
	return (sf::Keyboard::Unknown);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastFrame = sf::Time::Zero;
	sf::Time obstacleTimer = sf::seconds(6.0f);

	this->_timer.restart();
	while (this->window.isOpen())
	{
		timeSinceLastFrame += clock.restart();
		while (timeSinceLastFrame > TIME_PER_FRAME)
		{
			timeSinceLastFrame -= TIME_PER_FRAME;
			sf::Event event;
			while (this->window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed){
					this->window.close();
					this->setGameOver(true);
				}
			}
			if (this->getGameOver() == true){
				this->gameOverMenu(this->_timer.getElapsedTime());
				return;
			}
			sf::Keyboard::Key input = this->getInput(this->window);
			this->useInput(input);
			if (obstacleTimer.asSeconds() >= 6.0f) // 6 saniyede bir kontrol
			{
				this->createRandomBlock(OBSTACLE);
				this->createRandomBlock(FOOD);
				obstacleTimer = sf::Time::Zero; // Obstacle oluşturulduğunda zaman sıfırlanır
			}
			this->draw(this->window);
			obstacleTimer += TIME_PER_FRAME;
		}
	}
}

void	Game::moveSnake(string input){
	int	row_diff = 0;
	int	col_diff = 0;

	if (this->getDirections(row_diff, col_diff, input) == 1)
		return ;
	this->checkCollision();
	if (this->getGameOver() == true)
		return ;
	this->iterateSnake(row_diff, col_diff);
}

void	Game::iterateSnake(int x_dir, int y_dir){
	int temp_row , temp_col;

	temp_row = this->_snake->getX() - x_dir;
	temp_col = this->_snake->getY() - y_dir;

	if (this->getSnakeSize() > 1){
		for (int i = 1; i < this->getSnakeSize() ; i++){
			int	temp_row2 = this->_snake[i].getX();
			int	temp_col2 = this->_snake[i].getY();
			this->_snake[i].setX(temp_row);
			this->_snake[i].setY(temp_col);
			temp_row = temp_row2;
			temp_col = temp_col2;
		}
	}
	if (this->_map.getMapElement(this->_snake->getX(), this->_snake->getY()) == FOOD){
		Snake	*temp = new Snake[this->getSnakeSize() + 1];
		for (int i = 0; i < this->getSnakeSize(); i++){
			temp[i].setX(this->_snake[i].getX());
			temp[i].setY(this->_snake[i].getY());
		}
		delete [] this->_snake;
		this->_snake = temp;
		this->_snake[this->getSnakeSize()].setX(temp_row);
		this->_snake[this->getSnakeSize()].setY(temp_col);
		this->setScore(this->getScore() + 1);
		this->setSnakeSize(this->getSnakeSize() + 1);
		this->createRandomBlock(FOOD);
	}
	this->_map.deleteAllMapElements();
	this->addSnakeToMap();
}

int	Game::getDirections(int &x, int &y, string input){
	if (input == "W" || input == "w"){
		x = 0;
		y = -1;
	}
	else if (input == "s" || input == "S"){
		x = 0;
		y = 1;
	}
	else if (input == "a" || input == "A"){
		x = -1;
		y = 0;
	}
	else if (input == "d" || input == "D"){
		x = 1;
		y = 0;
	}
	if ((this->_map.getMapElement(this->_snake->getX() + x, this->_snake->getY() + y) == BOUNDARY) ||
		(this->_snake[0].getX() + x == this->_snake[1].getX() && this->_snake[0].getY() + y == this->_snake[1].getY()))
		return 1;
	this->_snake->setX(this->_snake->getX() + x);
	this->_snake->setY(this->_snake->getY() + y);
	return 0;
}

void	Game::checkCollision()
{
	int index = 1;

	if (this->_snake->getX() < 0 || this->_snake->getX() >= WIDTH || this->_snake->getY() < 0 || this->_snake->getY() >= HEIGHT) // check if snake is out of board
		this->setGameOver(true);
	while (index < this->getSnakeSize())
	{
		if (this->_snake->getX() == this->_snake[index].getX() &&
			this->_snake->getY() == this->_snake[index].getY() &&
			index != this->getSnakeSize() - 1) // check if snake hit itself
			this->setGameOver(true);
		index++;
	}
	if (this->_map.getMapElement(this->_snake->getX(), this->_snake->getY()) == OBSTACLE) // check if snake hit obstacle
		this->setGameOver(true);
}


int	Game::getSnakeSize(void) const
{
	return (this->_snakeSize);
}

void	Game::setSnakeSize(int size)
{
	this->_snakeSize = size;
}

void	Game::setScore(int score)
{
	this->_score = score;
}

int		Game::getScore(void) const
{
	return (this->_score);
}

void	Game::setName(string name)
{
	this->_name = name;
}

string	Game::getName(void) const
{
	return (this->_name);
}

void	Game::setGameOver(bool gameOver)
{
	this->_gameOver = gameOver;
}

bool	Game::getGameOver(void) const
{
	return (this->_gameOver);
}

void	Game::addSnakeToMap(void){
	for (int i = 0; i < this->getSnakeSize(); i++){
		if (i == 0)
			this->_map.setMapElement(this->_snake[i].getX(), this->_snake[i].getY(), PLAYER);
		else
			this->_map.setMapElement(this->_snake[i].getX(), this->_snake[i].getY(), BODY);
	}
}

void Game::mainMenu()
{
	std::string		playerNameString;
	sf::Text		playerName = this->_mainMenu->getPlayerName();

	while (this->window.isOpen())
	{
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				this->window.close();
				this->setGameOver(true);
			}
			else if (this->getGameOver() == true)
				this->window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Escape) {
					this->window.close();
					this->setGameOver(true);
				}
				else if (event.key.code == sf::Keyboard::Key::Return) {
					this->_mainMenu->select(playerNameString, *this);
				}
				else if (event.key.code == sf::Keyboard::Key::Down) {
					this->_mainMenu->downArrow();
				}
				else if (event.key.code == sf::Keyboard::Key::Up) {
					this->_mainMenu->upArrow();
				}
				else if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
					playerNameString += event.key.code + 65;
					playerName.setString(playerNameString);
					this->_mainMenu->setPlayerName(playerNameString);
				}
				else if (event.key.code == sf::Keyboard::Key::BackSpace) {
					if (!playerNameString.empty())
					{
						playerNameString.pop_back();
						playerName.setString(playerNameString);
						this->_mainMenu->setPlayerName(playerNameString);
					}
				}
			}
		}
		this->_mainMenu->draw(this->window);
	}
}

void Game::tutorial()
{
	sf::Font font;
	font.loadFromFile(FONT);

	sf::Text tutorialText("Snake Game Tutorial\n", font, 16);
	tutorialText.setPosition(20, 20);
	tutorialText.setFillColor(sf::Color::White);
	tutorialText.setString("Objective:"
		"Your goal is to control the snake and eat the food to grow.\n" "Avoid hitting walls and obstacles, as well as running into yourself.\n\n"
		"Controls:"
		"Use the arrow keys (W, A, S, D) to control the snake's movement.\nPress 'Esc' to exit the game at any time.\n\n"
		"Scoring:\n"
		"Each food item you eat adds 1 point to your score. Try to achieve the highest score possible.\n\n"
		"Obstacles:\n"
		"Obstacles will appear over time, so be careful not to run into them.\n" "Press 'Enter' to return to the main menu.\nPress 'Space' to start the game.\n");

	while (this->window.isOpen())
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                this->window.close();
                this->setGameOver(true);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Escape)
                {
                    this->window.close();
                    this->setGameOver(true);
                }
                else if (event.key.code == sf::Keyboard::Key::Return)
                {
                    // Return to the main menu when Enter key is pressed
                    this->window.clear();
                    this->window.display();
                    return;
                }
				else if (event.key.code == sf::Keyboard::Key::Space)
				{
					this->run();
				}
            }
        }

        this->window.clear();
        this->window.draw(tutorialText);
        this->window.display();
    }
}

void Game::gameOverMenu(sf::Time elapsedTime)
{
	this->_gameOverMenu->setProperties(this->getName(), (this->getScore()), elapsedTime);
	while (this->window.isOpen())
	{
		sf::Event event;
		while (this->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->window.close();
				this->setGameOver(true);
			}
			else if (this->_gameOverMenu->getExitGame() == true){
					this->window.close();
					this->setGameOver(true);
				}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Key::Escape) {
					this->window.close();
					this->setGameOver(true);
				}
				else if (event.key.code == sf::Keyboard::Key::Return){

					this->_gameOverMenu->select(this->getName(), *this);
				}
				else if (event.key.code == sf::Keyboard::Key::Down){
					this->_gameOverMenu->downArrow();
				}
				else if (event.key.code == sf::Keyboard::Key::Up){
					this->_gameOverMenu->upArrow();
				}
				else if (event.key.code == sf::Keyboard::Key::Space) {
					this->resetGame();
					this->run();
				}
				else if (event.key.code == sf::Keyboard::Key::S){
					this->setLeaderBoard(this->getName(), this->getScore());
				}
			}
		}
		this->_gameOverMenu->draw(this->window);
	}
}

void Game::resetGame()
{
	this->setScore(0);
	this->setSnakeSize(1);
	this->setGameOver(false);
	this->_map.clearMap(); // Haritayı temizle
	this->createRandomBlock(PLAYER); // Yeni bir oyuncu bloğu oluştur
	this->createRandomBlock(FOOD); // Yeni bir
}

void Game::useInput(sf::Keyboard::Key input){
	if (input == sf::Keyboard::Escape)
		this->window.close();
	else if (input == sf::Keyboard::W)
		this->moveSnake("W");
	else if (input == sf::Keyboard::S)
		this->moveSnake("S");
	else if (input == sf::Keyboard::A)
		this->moveSnake("A");
	else if (input == sf::Keyboard::D)
		this->moveSnake("D");
}

void	Game::draw(sf::RenderWindow &window){
	this->window.clear();
	this->_map.printMap(this->window, this->_texture.getBackgroundSprite(), this->_texture.getFoodSprite(),
						this->_texture.getObstacleSprite(), this->_texture.getPlayerSprite(),
						this->_texture.getBodySprite(), this->_texture.getBoundarySprite());
	this->window.display();
}
