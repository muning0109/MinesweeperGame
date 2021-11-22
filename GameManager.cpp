#include "GameManager.h"
#include "fstream"
#include "Board.h"
#include "SFML/Graphics.hpp"
#include "iostream"
using namespace std;


void GameManager::LoadFile()
{
    fstream configFile;
    configFile.open("boards/config.cfg", ios::in);
    string line;
    while(configFile.good())
    {
        getline(configFile,line);
        width = stoi(line);
        getline(configFile,line);
        height = stoi(line);
        getline(configFile,line);
        numMines = stoi(line);
    }
}

void GameManager::Run()
{
    LoadFile();
    Board board(width, height, numMines);
    sf::RenderWindow window(sf::VideoMode(width*32, height*32+88), "Minesweeper");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed) {
                bool leftClick = (event.mouseButton.button == sf::Mouse::Left);
                board.Click(leftClick,event.mouseButton.x,event.mouseButton.y);
            }
        }
        // clear the window with black color
        window.clear(sf::Color::White);

        // window.draw(...);
        board.Draw(&window);


        // end the current frame
        window.display();
    }
}



