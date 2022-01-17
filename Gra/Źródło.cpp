// Hello world! Cplayground is an online sandbox that makes it easy to try out
// code.



#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include<iostream>
#include "Menu.h"
#include<conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>

int windowWidth = 1000;
int windowHeight = 800;


using namespace sf;
using namespace std;


typedef struct {                                                                                                                                                      //struktura
    char nazwa[20];
    int liczb_pkt;
    char plec;
} gracz_cechy;


Menu::Menu(float width, float height) {                     //MENU

    if (!font.loadFromFile("pliki/sitka.ttf")) {          //ladowanie czcionki z pliku


    }

    menu[0].setFont(font);
    menu[0].setFillColor(Color(201, 173, 48));
    menu[0].setString("Wyniki graczy");
    menu[0].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setString("poziom podstawowy");
    menu[1].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setString("poziom trudny");
    menu[2].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    menu[3].setFont(font);
    menu[3].setString("wyjscie");
    menu[3].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));
}
Menu::~Menu() {}

void Menu::draw(RenderWindow& window) {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        window.draw(menu[i]);
}
void Menu::MoveUp() {

    if (selectedItemIndex >= 0 && selectedItemIndex < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        menu[selectedItemIndex].setStyle(sf::Text::Regular);
        selectedItemIndex--;
        if (selectedItemIndex < 0)
            selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
        menu[selectedItemIndex].setFillColor(Color(46, 104, 61));
        menu[selectedItemIndex].setStyle(sf::Text::Bold);
    }
}
void Menu::MoveDown() {

    if (selectedItemIndex >= 0 && selectedItemIndex < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        menu[selectedItemIndex].setStyle(sf::Text::Regular);
        selectedItemIndex++;
        if (selectedItemIndex >= MAX_NUMBER_OF_ITEMS)
            selectedItemIndex = 0;
        menu[selectedItemIndex].setFillColor(sf::Color(46, 104, 61));
        menu[selectedItemIndex].setStyle(sf::Text::Bold);
    }
}




void players_to_file()                              //ZAPIS DANYCH O GRACZACH
{
    srand(time(NULL));
    gracz_cechy playerschar[10];

    FILE* fp;
    fp = fopen("gracze.dat", "w+b");

    strcpy(playerschar[0].nazwa, "Jack");
    strcpy(playerschar[1].nazwa, "Tabisha");
    strcpy(playerschar[2].nazwa, "Derrick");
    strcpy(playerschar[3].nazwa, "Patty");
    strcpy(playerschar[4].nazwa, "Lucy");
    strcpy(playerschar[5].nazwa, "Stacy");
    strcpy(playerschar[6].nazwa, "Jack");
    strcpy(playerschar[7].nazwa, "Annie");
    strcpy(playerschar[8].nazwa, "Tiffany");
    strcpy(playerschar[9].nazwa, "Amy");

    for (int i = 0; i < 10; i++)
        playerschar[i].liczb_pkt = rand() % 5000;   //generowanie losowych wynikow 10 graczy w rankingu
    playerschar[0].plec = 'm';
    playerschar[1].plec = 'w';
    playerschar[2].plec = 'm';
    playerschar[3].plec = 'w';
    playerschar[4].plec = 'm';
    playerschar[5].plec = 'w';
    playerschar[6].plec = 'm';
    playerschar[7].plec = 'w';
    playerschar[8].plec = 'w';
    playerschar[9].plec = 'w';
    fwrite(playerschar, sizeof(gracz_cechy), 10, fp);
    fclose(fp);
}

int porownaj(const void* left, const void* right) {
    const gracz_cechy* a = (const gracz_cechy*)left;
    const gracz_cechy* b = (const gracz_cechy*)right;
    if (a->liczb_pkt > b->liczb_pkt) {
        return -1;
    }
    else if (a->liczb_pkt < b->liczb_pkt) {
        return 1;
    }
    else {
        return 0;
    }
}

class players_list {
private:
    sf::Text* players;
    gracz_cechy* player_char;
    sf::Font czcionka;
    int Np;
public:
    players_list(int N);
    void laduj();
    void sortuj();
    void draw(sf::RenderWindow& window);
};
players_list::players_list(int N)
{

    if (!czcionka.loadFromFile("pliki/sitka.ttf"))
        return;

    FILE* fp = fopen("gracze.dat", "r+b");
    unsigned int rozmiar_plik = 0, ile_graczy = 0;
    fseek(fp, 0, SEEK_END);                            //na ostatni bajt
    rozmiar_plik = ftell(fp);                         //czytaj indeks ostatniego bajtu
    ile_graczy = rozmiar_plik / sizeof(gracz_cechy);
    if (N > ile_graczy)
    {
        Np = 2;                                       //zabezpiecza przed odczytaniem nieistniejacych danych
    }
    else
    {
        Np = N;
    }

    players = new sf::Text[Np];
    player_char = new gracz_cechy[Np];

    rewind(fp);                                          //czytaj od poczatku
    fread(player_char, sizeof(gracz_cechy), Np, fp);
    fclose(fp);

    for (int i = 0; i < Np; i++)
    {
        players[i].setFont(czcionka);
        players[i].setCharacterSize(30);
        players[i].setFillColor(sf::Color(235, 199, 19));
        players[i].setPosition(10 + 800 / 4, 20 + i * 50);

    }
}

void players_list::laduj()
{
    std::string tmp_tekst;
    for (int i = 0; i < Np; i++)
    {
        players[i].setFont(czcionka);
        players[i].setCharacterSize(15);
        players[i].setFillColor(Color(242, 146, 29));
        players[i].setPosition(330, 100 + i * 20);

        tmp_tekst.assign(player_char[i].nazwa);
        tmp_tekst += " punkty: " + std::to_string(player_char[i].liczb_pkt);
        if (player_char[i].plec == 'm')
            tmp_tekst += " Mezczyzna\n";
        if (player_char[i].plec == 'w')
            tmp_tekst += " Kobieta\n";
        players[i].setString(tmp_tekst);
    }
}

void players_list::sortuj()
{
    qsort(player_char, Np, sizeof(gracz_cechy), porownaj);
}

void players_list::draw(sf::RenderWindow& window)
{
    Font sitkaFont;
    sitkaFont.loadFromFile("pliki/sitka.ttf");
    Text wynikiText("Ranking:", sitkaFont, 30);
    wynikiText.setPosition(Vector2f(325, 20));
    wynikiText.setFillColor(Color(63, 164, 186));
    window.draw(wynikiText);
    for (int i = 0; i < Np; i++)
    {
        window.draw(players[i]);
    }
}


class playerClass {
public:
    bool playerFaceRight;               //kierunek chodu 
    bool onGround;                      //czy postac dotyka podloza
    float xPos;
    float xV;
    playerClass() {
        playerFaceRight = true;
        xPos = 600;                       //pozycja 
        xV = 0;                         //predkosc 
        onGround = false;

    }

    void update(bool playerLeft, bool playerRight) {   //aktualizacja danych postaci
        if (playerRight) {
            playerFaceRight = true;
            xV = 0.1;
        }
        if (playerLeft) {
            playerFaceRight = false;     //gdy w lewo
            xV = -0.1;
        }
        if (!(playerRight || playerLeft)) { //zatrzymuje gracza jesli nie chodzi
            xV = 0;

        }
        xPos += xV;                     // przesuwa pozycje gracza

    }
};
/*class Bullet {
public:
    Bullet(sf::Vector2f size) {
        bullet.setSize(size);
        bullet.setFillColor(sf::Color::Blue);
    }

    void fire(int speed) {
        bullet.move(speed, 0);
    }

    int getRight() {
        return bullet.getPosition().x + bullet.getSize().x;
    }

    int getLeft() {
        return bullet.getPosition().x;
    }

    int getTop() {
        return bullet.getPosition().y;
    }

    int getBottom() {
        return bullet.getPosition().y + bullet.getSize().y;
    }

    void setPos(sf::Vector2f newPos) {
        bullet.setPosition(newPos);
    }

private:
    sf::RectangleShape bullet;
};
*/


int main()                          //MAIN
{
    int read_flag = 0;              //Zmienna Save/Load
    int difficultyLevel = 0;        //zmienna Trudnosci
    int score = 1;                  //score
    bool helpPage = false;
    bool isMenuOpen = true;         //sprawdza czy jest sie w menu
    bool helpScreen = false;        //sprawdza czy otwarta jest pomoc
    bool quitScreen = false;        //ESC ekran
    bool isPlaying = false;         //sprawdza czy sie gra
    bool dead = true;             //zmienna czy zyje postac

                                                                                                        //render window
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Gra");

    Menu menu(window.getSize().x, window.getSize().y);


    int x = 0, y = 0;//pozycja 
    int dx = 10, dy = 0;
    bool playerLeft, playerRight = false;  //zmienne ruchu

    playerClass playerObject;
    //std::vector<Bullet> bulletVec;
    //bool isFiring = false;
    // 
    // 
    //pomoc dla gracza H
    Font sitkaFont;
    sitkaFont.loadFromFile("pliki/sitka.ttf");
    Text helpText("Strzalka w lewo - ruch w lewo\nStrzalka w prawo - ruch w prawo\nS - zapisz\n/R - wczytaj \nEsc - wyjscie", sitkaFont, 35);
    helpText.setPosition(Vector2f(50, 150));
    helpText.setFillColor(Color(50, 168, 82));

    //Ekran ESC
    Text quitText("E - wyjscie z gry", sitkaFont, 30);
    quitText.setPosition(Vector2f(600, 150));
    quitText.setFillColor(Color(50, 168, 82));

    //TYTUL
    Text themeText("Symulator krewetki", sitkaFont, 50);
    themeText.setPosition(Vector2f(250, 0));

    //sprite ryby
    Texture enemy1Texture;                                                            //obszar prostokątny sprite’a jakoniezależny obiekt, np..sf::IntRect
    enemy1Texture.loadFromFile("pliki/ryba.png");
    IntRect rectEnemySprite(0, -12, 188, 122);
    Sprite enemySprite(enemy1Texture, rectEnemySprite);                                            //Construct the sprite from a sub-rectangle of a source texture
                                                                            //sprite krewetki
    Texture playerTexture;
    playerTexture.loadFromFile("pliki/krewetka.PNG");
    IntRect rectSourceSprite(0, 0, 42, 50);                                                                                                                          //setTexture(NULL)
    Sprite playerSprite(playerTexture, rectSourceSprite);
    playerSprite.setPosition(480.f, 535.f);


    //sprite dna
    Texture groundTexture;
    groundTexture.loadFromFile("pliki/dno1.png");
    IntRect rectGroundSprite(0, 0, 980, 60);
    Sprite groundSprite(groundTexture, rectGroundSprite);
    groundSprite.setPosition(10.f, 600.f);


    Text scoreText("tak trzymaj", sitkaFont, 20);
    scoreText.setPosition(Vector2f(600, 500));
    scoreText.setFillColor(Color(230, 115, 0));

    Clock clock;                                 //zegary
    Clock enemyClock;
    Clock scoreClock;


    players_to_file();                           //Wyniki
    players_list* pl = new players_list(10);
    pl->sortuj();
    pl->laduj();

    //Petla gry
    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event))
        {

            //MENU
            switch (event.type)
            {
            case Event::KeyReleased:
                switch (event.key.code)
                {
                case Keyboard::Up:
                    menu.MoveUp();
                    break;
                case Keyboard::Down:
                    menu.MoveDown();
                    break;
                case Keyboard::Return:
                    switch (menu.getSelectedItem())
                    {
                    case 0:
                        cout << "Wyniki" << endl;
                        isMenuOpen = false;
                        isPlaying = false;
                        dead = true;
                        break;
                    case 1:
                        cout << "rozpocznij gre na poziomie latwym" << endl;
                        isPlaying = true;
                        isMenuOpen = false;
                        dead = false;
                        difficultyLevel = 1;
                        break;
                    case 2:
                        cout << "rozpocznij gre na poziomie trudnym" << endl;
                        isPlaying = true;
                        isMenuOpen = false;
                        dead = false;
                        difficultyLevel = 2;
                        break;
                    case 3:
                        cout << "Wyjscie z gry" << endl;
                        window.close();
                        break;
                    }
                    break;
                }
            }
            //koniec MENU

            if (event.type == Event::Closed)
                window.close();
        }


        if (clock.getElapsedTime().asMilliseconds() > 100.0f) {
            if (rectSourceSprite.left == 120)
                rectSourceSprite.left = 0;
            else
                rectSourceSprite.left += 60;
            playerSprite.setTextureRect(rectSourceSprite);
            clock.restart();
        }



        helpScreen = false;
        if (Keyboard::isKeyPressed(Keyboard::H))helpScreen = true;


        //sterowanie strzalkami lewo i prawo
        if (Keyboard::isKeyPressed(Keyboard::Right))playerRight = true;
        if (Keyboard::isKeyPressed(Keyboard::Left))playerLeft = true;
        if (!(Keyboard::isKeyPressed(Keyboard::Left)))playerLeft = false;
        if (!(Keyboard::isKeyPressed(Keyboard::Right)))playerRight = false;
        playerObject.update(playerLeft, playerRight);

        if (Keyboard::isKeyPressed(Keyboard::S)) {
            read_flag = 0;              //sprawdza czy wczytac zapis
            ofstream savefile1;
            savefile1.open("playerState.txt", ios::out | ios::trunc);   //utworzenie txt
            savefile1.write((const char*)&playerObject, sizeof(playerObject)); //zapisanie w txt
            savefile1.close();
            cout << "Zapis!\n";
        }

        if (Keyboard::isKeyPressed(Keyboard::R)) {
            ifstream savefile2;
            cout << "Odczyt!\n";
            read_flag = 1;
            savefile2.open("playerState.txt", ios::in);
            savefile2.seekg(0);                     //przesuwa wzkaznik odczytu na 0
            savefile2.read((char*)&playerObject, sizeof(playerObject));
            printf("\nxPos :%f", playerObject.xPos);
            playerObject.xPos = playerObject.xPos; //pozycjonuje gracza
            savefile2.close();
        }



        ///losowy ruch przeciwnika, predkosc zalezna od poziomu trudnosci 
        if (enemyClock.getElapsedTime().asMilliseconds() > 400.0f / difficultyLevel) {
            enemySprite.setPosition(rand() % 1100 + 1, 0.f);
            enemyClock.restart();
        }


        //czysci okno
        if (difficultyLevel == 0)
            window.clear(Color(0, 0, 0)); //kolor tla

        if (difficultyLevel == 1)
            window.clear(Color(0, 0, 0));

        if (difficultyLevel == 2)
            window.clear(Color(0, 0, 0));

        if (isMenuOpen == true) {           //sprawdza czy jest sie w menu
            menu.draw(window);
            window.draw(themeText);         //tytul gry
        }

        if (isPlaying == true && dead == false) {

            window.draw(playerSprite);
            window.draw(groundSprite);
            window.draw(enemySprite);

            playerSprite.setPosition(playerObject.xPos, 535.f);

            //EKRAN HELP 
            if (helpScreen == true)
                window.draw(helpText);


            //ekran escape
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.draw(quitText);


            if (Keyboard::isKeyPressed(Keyboard::E))
                window.close();                                                                                                                                //zamyka gre
        }


        if (isPlaying == false && isMenuOpen == false) {                                                                                        //wyswietla wyniki gdy sie nie gra i gdy nie jest sie w menu
            if (dead == true) {
            }
            pl->draw(window);
        }
        window.display();

    }


    return 0;
}
