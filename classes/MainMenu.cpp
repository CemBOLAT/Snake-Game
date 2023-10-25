#include "../includes/MainMenu.hpp"
#include "../includes/Game.hpp"

using namespace std;

MainMenu::MainMenu(void)
{
	font.loadFromFile(FONT);
	titleText = sf::Text("Snake Game", font, 48);
	titleText.setPosition(WIDTH / 2 - titleText.getGlobalBounds().width / 2, 25);
	titleText.setFillColor(sf::Color::White);

	namePrompt = sf::Text("Enter your name : ", font, 24);
	namePrompt.setPosition(WIDTH / 2 - namePrompt.getGlobalBounds().width / 2, 100);
	namePrompt.setFillColor(sf::Color::White);

	playerName = sf::Text("", font, 24);
	playerName.setPosition(WIDTH - 160 - playerName.getGlobalBounds().width - 270, 150);
	playerName.setFillColor(sf::Color::White);

	startText = sf::Text("Start", font, 24);
	startText.setPosition(WIDTH / 2 - startText.getGlobalBounds().width / 2, 200);
	startText.setFillColor(sf::Color::White);

	tutorialText = sf::Text("Tutorial", font, 24);
	tutorialText.setPosition(WIDTH / 2 - tutorialText.getGlobalBounds().width / 2, 250);
	tutorialText.setFillColor(sf::Color::White);

	leaderboardText = sf::Text("Leaderboard", font, 24);
	leaderboardText.setPosition(WIDTH / 2 - leaderboardText.getGlobalBounds().width / 2, 300);
	leaderboardText.setFillColor(sf::Color::White);

	exitText = sf::Text("Exit", font, 24);
	exitText.setPosition(WIDTH / 2 - exitText.getGlobalBounds().width / 2, 350);
	exitText.setFillColor(sf::Color::White);

	startText.setFillColor(sf::Color::Yellow);

	selectedText = "Start";
}

MainMenu::MainMenu(MainMenu const & src)
{
	*this = src;
}

MainMenu::~MainMenu(void){}

sf::Text		MainMenu::getTitleText(void) const
{
	return (titleText);
}

sf::Text		MainMenu::getNamePrompt(void) const
{
	return (namePrompt);
}

sf::Text		MainMenu::getPlayerName(void) const
{
	return (playerName);
}

sf::Text		MainMenu::setPlayerName(string name)
{
	playerName.setString(name);
	playerName.setPosition(WIDTH - (name.size() * 10) - playerName.getGlobalBounds().width - (name.size() * 15), 150);
	return (playerName);
}

sf::Text		MainMenu::getStartText(void) const
{
	return (startText);
}

sf::Text		MainMenu::getTutorialText(void) const
{
	return (tutorialText);
}

sf::Text		MainMenu::getLeaderboardText(void) const
{
	return (leaderboardText);
}

sf::Text		MainMenu::getExitText(void) const
{
	return (exitText);
}

void	MainMenu::draw(sf::RenderWindow &window)
{
	window.clear();
	window.draw(titleText);
	window.draw(namePrompt);
	window.draw(playerName);
	window.draw(startText);
	window.draw(tutorialText);
	window.draw(leaderboardText);
	window.draw(exitText);
	window.display();
}


void	MainMenu::select(string playerNameString, Game &gameObjec)
{
	if (selectedText == "Start" && !playerNameString.empty())
	{
		gameObjec.setName(playerNameString);
		gameObjec.run();
	}
	else if (selectedText == "Tutorial")
	{
		gameObjec.tutorial();
	}
	else if (selectedText == "Leaderboard")
	{
		gameObjec.getLeaderBoardScene();
	}
	else if (selectedText == "Exit")
	{
		gameObjec.setGameOver(true);
	}
}


void	MainMenu::downArrow(){
	if (selectedText == "Start")
	{
		startText.setFillColor(sf::Color::White);
		selectedText = "Tutorial";
		tutorialText.setFillColor(sf::Color::Yellow);
	}
	else if (selectedText == "Tutorial")
	{
		tutorialText.setFillColor(sf::Color::White);
		selectedText = "Leaderboard";
		leaderboardText.setFillColor(sf::Color::Yellow);
	}
	else if (selectedText == "Leaderboard")
	{
		leaderboardText.setFillColor(sf::Color::White);
		selectedText = "Exit";
		exitText.setFillColor(sf::Color::Yellow);
	}
	else if (selectedText == "Exit")
	{
		exitText.setFillColor(sf::Color::White);
		selectedText = "Start";
		startText.setFillColor(sf::Color::Yellow);
	}
}

void	MainMenu::upArrow(){
	if (selectedText == "Start")
	{
		startText.setFillColor(sf::Color::White);
		selectedText = "Exit";
		exitText.setFillColor(sf::Color::Yellow);
	}
	else if (selectedText == "Tutorial")
	{
		tutorialText.setFillColor(sf::Color::White);
		selectedText = "Start";
		startText.setFillColor(sf::Color::Yellow);
	}
	else if (selectedText == "Leaderboard")
	{
		leaderboardText.setFillColor(sf::Color::White);
		selectedText = "Tutorial";
		tutorialText.setFillColor(sf::Color::Yellow);
	}
	else if (selectedText == "Exit")
	{
		exitText.setFillColor(sf::Color::White);
		selectedText = "Leaderboard";
		leaderboardText.setFillColor(sf::Color::Yellow);
	}
}
