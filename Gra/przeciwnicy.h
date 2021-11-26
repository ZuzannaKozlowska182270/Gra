#pragma once
#include <SFML/Graphics.hpp>

class ryba {
public:
	ryba(int N);
	void draw(sf::RenderWindow& window);
	void move();


	void ryby::draw(sf::RenderWindow& window) {
		for (int i = 0; i < N; i++)
		{
			window.draw(ryba[i]);
		}
	}
private:
	int N;
};

