#include "../includes/GameOver.hpp"
#include <string>

GameOver::GameOver(){

	font.loadFromFile(FONT);

	saveText = sf::Text("Save (S)", font, 36);
	saveText.setPosition(WIDTH / 2 - saveText.getGlobalBounds().width / 2, 300);
	saveText.setFillColor(sf::Color::Red);

	restartText = sf::Text("Restart (Space)", font, 36);
	restartText.setPosition(WIDTH / 2 - restartText.getGlobalBounds().width / 2, 350);
	restartText.setFillColor(sf::Color::White);

	exitText = sf::Text("Exit (Esc)", font, 36);
	exitText.setPosition(WIDTH / 2 - exitText.getGlobalBounds().width / 2, 400);
	exitText.setFillColor(sf::Color::White);

	selectedText = "Save";
	exit_game = false;
}

GameOver::GameOver(GameOver const & src){
	*this = src;
}

GameOver::~GameOver(void){}

sf::Text		GameOver::getGameOverText(void) const{
	return (gameOverText);
}

sf::Text		GameOver::getScoreStr(void) const{
	return (scoreText);
}

sf::Text		GameOver::getTimeText(void) const{
	return (timeText);
}

sf::Text		GameOver::getRestartText(void) const{
	return (restartText);
}

sf::Text		GameOver::getExitText(void) const{
	return (exitText);
}

sf::Text		GameOver::getSaveText(void) const{
	return (saveText);
}

void			GameOver::draw(sf::RenderWindow &window){
	window.clear();
	window.draw(gameOverText);
	window.draw(scoreText);
	window.draw(timeText);
	window.draw(restartText);
	window.draw(saveText);
	window.draw(exitText);
	window.display();
}

void			GameOver::select(string playerNameString, Game &gameObjec){
	if (selectedText == "Restart"){
		gameObjec.resetGame();
		gameObjec.setGameOver(false);
		this->setExitGame(false);
		gameObjec.run();
	}
	else if (selectedText == "Save"){
		gameObjec.setLeaderBoard(playerNameString, gameObjec.getScore());
	}
	else if (selectedText == "Exit"){
		this->setExitGame(true);
	}
}

void			GameOver::upArrow(){
	if (selectedText == "Restart"){
		selectedText = "Save";
		saveText.setFillColor(sf::Color::Red);
		restartText.setFillColor(sf::Color::White);
	}
	else if (selectedText == "Save"){
		selectedText = "Exit";
		exitText.setFillColor(sf::Color::Red);
		saveText.setFillColor(sf::Color::White);
	}
	else if (selectedText == "Exit"){
		selectedText = "Restart";
		restartText.setFillColor(sf::Color::Red);
		exitText.setFillColor(sf::Color::White);
	}
}

void			GameOver::downArrow(){
	if (selectedText == "Restart"){
		selectedText = "Exit";
		exitText.setFillColor(sf::Color::Red);
		restartText.setFillColor(sf::Color::White);
	}
	else if (selectedText == "Save"){
		selectedText = "Restart";
		restartText.setFillColor(sf::Color::Red);
		saveText.setFillColor(sf::Color::White);
	}
	else if (selectedText == "Exit"){
		selectedText = "Save";
		saveText.setFillColor(sf::Color::Red);
		exitText.setFillColor(sf::Color::White);
	}
}

void	GameOver::setProperties(string name, int score, sf::Time elapsedTime){
	this->name = name;
	this->score = score;
	this->_elapsedTime = elapsedTime;

	string	scoreStr = "Score: " + std::to_string(this->score);

	gameOverText = sf::Text("Game Over  " + name , font, 48);
	gameOverText.setPosition(WIDTH / 2 - gameOverText.getGlobalBounds().width / 2, 100);
	gameOverText.setFillColor(sf::Color::White);

	scoreText = sf::Text(scoreStr, font, 36);
	scoreText.setPosition(WIDTH / 2 - scoreText.getGlobalBounds().width / 2, 200);
	scoreText.setFillColor(sf::Color::White);

	int totalSeconds = int(this->_elapsedTime.asSeconds());
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;
	timeText = sf::Text("Elapsed Time: " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s", font, 36);
	timeText.setPosition(WIDTH / 2 - timeText.getGlobalBounds().width / 2, 250);
	timeText.setFillColor(sf::Color::White);
}

std::string	GameOver::getSelectedText(void) const{
	return (selectedText);
}

void		GameOver::setSelectedText(std::string text){
	selectedText = text;
}

bool	GameOver::getExitGame(void) const{
	return (exit_game);
}

void	GameOver::setExitGame(bool exit){
	exit_game = exit;
}
