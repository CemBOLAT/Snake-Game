#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Defines.h"

class Texture
{
	private:
		sf::Font			font;
		sf::Texture			backgroundTexture;
		sf::Texture			foodTexture;
		sf::Texture			obstacleTexture;
		sf::Texture			playerTexture;
		sf::Texture			bodyTexture;
		sf::Texture			boundaryTexture;
		sf::Sprite			backgroundSprite;
		sf::Sprite			foodSprite;
		sf::Sprite			obstacleSprite;
		sf::Sprite			playerSprite;
		sf::Sprite			bodySprite;
		sf::Sprite			boundarySprite;
	public:
		Texture(void);
		Texture(Texture const & src);
		~Texture(void);
		Texture & operator=(Texture const & copy);

		sf::Sprite			getBackgroundSprite(void) ;
		sf::Sprite			getFoodSprite(void) ;
		sf::Sprite			getObstacleSprite(void) ;
		sf::Sprite			getPlayerSprite(void) ;
		sf::Sprite			getBodySprite(void) ;
		sf::Sprite			getBoundarySprite(void) ;

		sf::Font			getFont(void) const;
};
