#include "../includes/Texture.hpp"
#include <iostream>

Texture::Texture(void)
{
	this->backgroundTexture.loadFromFile(BG_TEX);
	this->foodTexture.loadFromFile(FOOD_TEX);
	this->obstacleTexture.loadFromFile(OBST_TEX);
	this->playerTexture.loadFromFile(PLAYER_TEX);
	this->bodyTexture.loadFromFile(BODY_TEX);
	this->boundaryTexture.loadFromFile(BOUND_TEX);
	font.loadFromFile(FONT);
	backgroundSprite.setTexture(backgroundTexture);
	foodSprite.setTexture(foodTexture);
	obstacleSprite.setTexture(obstacleTexture);
	playerSprite.setTexture(playerTexture);
	bodySprite.setTexture(bodyTexture);
	boundarySprite.setTexture(boundaryTexture);
}

Texture::Texture(Texture const & src)
{
	*this = src;
}

Texture::~Texture(void){}

Texture & Texture::operator=(Texture const & copy)
{
	if (this != &copy)
	{
		this->backgroundTexture = copy.backgroundTexture;
		this->foodTexture = copy.foodTexture;
		this->obstacleTexture = copy.obstacleTexture;
		this->playerTexture = copy.playerTexture;
		this->bodyTexture = copy.bodyTexture;
		this->boundaryTexture = copy.boundaryTexture;
		this->backgroundSprite = copy.backgroundSprite;
		this->foodSprite = copy.foodSprite;
		this->obstacleSprite = copy.obstacleSprite;
		this->playerSprite = copy.playerSprite;
		this->bodySprite = copy.bodySprite;
		this->boundarySprite = copy.boundarySprite;
	}
	return (*this);
}

sf::Sprite			Texture::getBackgroundSprite(void)
{
	return (this->backgroundSprite);
}

sf::Sprite			Texture::getFoodSprite(void)
{
	return (this->foodSprite);
}

sf::Sprite			Texture::getObstacleSprite(void)
{
	return (this->obstacleSprite);
}

sf::Sprite			Texture::getPlayerSprite(void)
{
	return (this->playerSprite);
}

sf::Sprite			Texture::getBodySprite(void)
{
	return (this->bodySprite);
}

sf::Sprite			Texture::getBoundarySprite(void)
{
	return (this->boundarySprite);
}

sf::Font			Texture::getFont(void) const
{
	return (this->font);
}
