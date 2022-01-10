#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 4

using namespace std;
using namespace sf;

class Menu
{
public:
	Menu(float width, float height);
	~Menu();


	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int getSelectedItem() { return selectedItemIndex; }//zwroc poziom menu

private:
	int selectedItemIndex;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];

};

