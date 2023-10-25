#include "../includes/Game.hpp"
#include "../includes/Defines.h"
#include <algorithm>
#include <fstream>
#include <istream>

using namespace std;
bool Comparator(const pair<string, int>& a, const pair<string, int>& b);

LeaderBoard::LeaderBoard(void) : _playerNum(0){

	_font.loadFromFile("./asset/fonts/arial_bold.ttf");
	exitText.setFont(_font);
	exitText.setCharacterSize(16);
	exitText.setFillColor(sf::Color::White);
	exitText.setString("Exit (ESC)");
	exitText.setPosition(WIDTH / 2 - exitText.getGlobalBounds().width / 2, 430);

	infoText.setFont(_font);
	infoText.setCharacterSize(16);
	infoText.setFillColor(sf::Color::White);
	infoText.setString("User | Score | Minute | Second");
	infoText.setPosition(WIDTH / 2 - infoText.getGlobalBounds().width / 2, 30);

	menuText.setFont(_font);
	menuText.setCharacterSize(16);
	menuText.setFillColor(sf::Color::White);
	menuText.setString("Menu (M)");
	menuText.setPosition(WIDTH / 2 - menuText.getGlobalBounds().width / 2, 380);

	this->initPlayerNum();

	this->allPlayers = new pair<string, int>[_playerNum];
	this->allTime = new pair<int, int>[_playerNum];
	this->_player = new pair<string, int>;
	this->readAndFill();
}

LeaderBoard::~LeaderBoard(void){
	delete [] this->_player;
	delete [] this->allPlayers;
	delete [] this->allTime;
}

void	LeaderBoard::initPlayerNum(void){
	ifstream	file(LEADERBOAD_TEXT_NAME);
	string		line;

	if (file.is_open()){
		while (getline(file, line)){
			_playerNum++;
		}
		file.close();
	}
}

int	LeaderBoard::getPlayerNum(void) const{
	return this->_playerNum;
}

void	LeaderBoard::setPlayerNum(int playerNum){
	this->_playerNum = playerNum;
}

void	LeaderBoard::readAndFill(void){
	ifstream	file(LEADERBOAD_TEXT_NAME);
	string		line;
	int			i = 0;

	if (file.is_open()){
		while (getline(file, line)){
			this->allPlayers[i].first = line.substr(0, line.find(" "));
			this->allPlayers[i].second = stoi(line.substr(line.find(" ") + 1, line.find(" ", line.find(" ") + 1) - line.find(" ") - 1));
			string timeData = line.substr(line.find(" ", line.find(" ") + 1) + 1);
			this->allTime[i].first = stoi(timeData.substr(0, timeData.find(" "))); // minute
			this->allTime[i].second = stoi(timeData.substr(timeData.find(" ") + 1)); // second
			i++;
		}
		file.close();
	}
}

void Game::getLeaderBoardScene(){
	sf::Text text;
	sf::Font font;

	sort(this->_leaderBoard.getAllPlayers(), this->_leaderBoard.getAllPlayers() + this->_leaderBoard.getPlayerNum(), Comparator);

	font.loadFromFile(FONT);
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	window.clear();

	for (int i = 0; i < min(10, _leaderBoard.getPlayerNum()); i++) {
		sf::String playerInfo = this->_leaderBoard.getAllPlayers()[i].first + " | "
								+ to_string(this->_leaderBoard.getAllPlayers()[i].second) + " | "
								+ to_string(this->_leaderBoard.getAllTime()[i].first) + " : "
								+ to_string(this->_leaderBoard.getAllTime()[i].second);
		text.setString(playerInfo);
		text.setPosition(WIDTH / 2 - text.getGlobalBounds().width / 2, 50 + i * 30);
		window.draw(text);
	}

	window.draw(this->_leaderBoard.getExitText());
	window.draw(this->_leaderBoard.getMenuText());
	window.draw(this->_leaderBoard.getInfoText());
	window.display();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					// ESC tuşuna basıldığında oyunu kapat
					window.close();
				} else if (event.key.code == sf::Keyboard::M) {
					// M tuşuna basıldığında menüye dön
					// Bu kısmı menü ekranını göstermek için çağırabilirsiniz
					this->mainMenu();
				}
			}
		}
	}
}

void Game::setLeaderBoard(string name, int score) {
	LeaderBoard& leaderboard = _leaderBoard; // LeaderBoard nesnesine erişim
	// Eğer aynı isme sahip bir kayıt varsa eklemeyin
	for (int i = 0; i < leaderboard.getPlayerNum(); i++) {
		if (this->_leaderBoard.getAllPlayers()[i].first == name
			&& this->_leaderBoard.getAllPlayers()[i].second == score) {
			return;
		}
	}

	pair<string, int>* tmp = new pair<string, int>[leaderboard.getPlayerNum() + 1];
	pair<int, int>* tmpTime = new pair<int, int>[leaderboard.getPlayerNum() + 1];
	for (int i = 0; i < leaderboard.getPlayerNum(); i++) {
		tmp[i] = this->_leaderBoard.getAllPlayers()[i];
		tmpTime[i] = this->_leaderBoard.getAllTime()[i];
	}
	tmp[leaderboard.getPlayerNum()] = make_pair(name, score);

	float elapsedTimeInSeconds = _timer.getElapsedTime().asSeconds();
	int minutes = static_cast<int>(elapsedTimeInSeconds) / 60;
	int seconds = static_cast<int>(elapsedTimeInSeconds) % 60;
	tmpTime[leaderboard.getPlayerNum()] = make_pair(minutes, seconds);

	this->_leaderBoard.delAllPlayers();
	this->_leaderBoard.delAllTime();

	this->_leaderBoard.setAllPlayers(tmp);
	this->_leaderBoard.setAllTime(tmpTime);
	leaderboard.setPlayerNum(leaderboard.getPlayerNum() + 1);
	sort(this->_leaderBoard.getAllPlayers(), this->_leaderBoard.getAllPlayers() + leaderboard.getPlayerNum(), Comparator);
	ofstream file(LEADERBOAD_TEXT_NAME);

	if (file.is_open()) {
		for (int i = 0; i < leaderboard.getPlayerNum(); i++) {
			file << this->_leaderBoard.getAllPlayers()[i].first << " " << this->_leaderBoard.getAllPlayers()[i].second;
			file << " " << this->_leaderBoard.getAllTime()[i].first << " " << this->_leaderBoard.getAllTime()[i].second << endl;
		}
		file.close();
	}
}

pair<string, int>* LeaderBoard::getAllPlayers(void) const{
	return this->allPlayers;
}

pair<string, int>* LeaderBoard::getPlayer(void) const{
	return this->_player;
}

pair<int, int>* LeaderBoard::getAllTime(void) const{
	return this->allTime;
}

void	LeaderBoard::delAllPlayers(void){
	delete [] this->allPlayers;
}

void	LeaderBoard::delAllTime(void){
	delete [] this->allTime;
}

void	LeaderBoard::delPlayer(void){
	delete [] this->_player;
}

void	LeaderBoard::setAllPlayers(pair<string, int> *allPlayers){
	this->allPlayers = allPlayers;
}

void	LeaderBoard::setAllTime(pair<int, int> *allTime){
	this->allTime = allTime;
}

void	LeaderBoard::setPlayer(pair<string, int> *player){
	this->_player = player;
}

sf::Text	LeaderBoard::getExitText(void) const{
	return this->exitText;
}

sf::Text	LeaderBoard::getMenuText(void) const{
	return this->menuText;
}

// Comparator işlevi, öğeleri puanlarına göre büyükten küçüğe sıralar.
bool Comparator(const pair<string, int>& a, const pair<string, int>& b) {
	if (a.second != b.second) {
		// Puanlar farklı ise, puanlara göre sırala
		return a.second > b.second;
	} else {
		// Puanlar aynı ise, zamanlara göre sırala
		// İlk olarak dakikaya göre, sonra saniyeye göre sırala
		if (a.first != b.first) {
			return a.first > b.first;
		} else {
			return a.second > b.second;
		}
	}
}

sf::Text	LeaderBoard::getInfoText(void) const{
	return this->infoText;
}
