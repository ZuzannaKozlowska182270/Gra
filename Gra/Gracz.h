
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

class Gracz {
public:
	Gracz() {

	}
	Gracz(std::string imgDirectory) {
		sf::Event event;
		sf::Texture pTexture;
		sf::Sprite Gracz(pTexture);


		if (!pTexture.loadFromFile(imgDirectory)) {
			std::cerr << "Error\n";
		}
		void drawGracz(sf::RenderWindow & window) {
			window.draw(pSprite);
		}
		Gracz(float x_in, float y_in);
		void moveGracz(float x_in, float y_in) {

			/*poruszanie siê tylko w P/G/D*/




		}
	}
private:
	sf::Vector2f position;
	float xVel = 10;
	float yVel = 10;

};
