#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 755, (sf::VideoMode::getDesktopMode().height / 2) - 390);
    sf::Clock zegar;



    window.create(sf::VideoMode(1500, 700)), "Gra", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);

    window.setKeyRepeatEnabled(true);
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))

        {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
    
      void Gra::spawn_przeciwnicy() {

        this->enemy.setPosition(
            rand()%this->window->getSize().x)
            );
    }
