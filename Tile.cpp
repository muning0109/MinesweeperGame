#include "Tile.h"
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "iostream"
using namespace std;

Tile::Tile(bool isMine, int i, int width, int height)
{
    neighbourMines = 0;
    this->isMine = isMine;
    isFlagged = false;
    isRevealed = false;
    upLeft = nullptr;
    up = nullptr;
    upRight = nullptr;
    right = nullptr;
    bottomRight = nullptr;
    bottom = nullptr;
    bottomLeft = nullptr;
    left = nullptr;
    xPos = i%width;
    yPos = i/width;
}

void Tile::Draw(sf::RenderWindow *window, bool debugMode, bool lost, bool win)
{

    if(!isFlagged && !isRevealed) {
        background.setTexture(TextureManager::GetTexture("tile_hidden"));
        background.setPosition(xPos * 32, yPos * 32);
        window->draw(background);
    }
    else if(isFlagged && !isRevealed)
    {
        background.setPosition(xPos*32,yPos*32);
        window->draw(background);
        flag.setTexture(TextureManager::GetTexture("flag"));
        flag.setPosition(xPos*32,yPos*32);
        window->draw(flag);
    } else if (isFlagged && !isRevealed){
        background.setTexture(TextureManager::GetTexture("tile_hidden"));
        background.setPosition(xPos*32,yPos*32);
        window->draw(background);
        flag.setTexture(TextureManager::GetTexture("flag"));
        flag.setPosition(xPos*32,yPos*32);
        window->draw(flag);
    }else if(isMine && isRevealed && !isFlagged) {
        background.setTexture(TextureManager::GetTexture("tile_revealed"));
        background.setPosition(xPos*32,yPos*32);
        window->draw(background);
        foreground.setTexture(TextureManager::GetTexture("mine"));
        foreground.setPosition(xPos*32,yPos*32);
        window->draw(foreground);
    } else if(!isMine && isRevealed){
        background.setTexture(TextureManager::GetTexture("tile_revealed"));
        background.setPosition(xPos*32,yPos*32);
        window->draw(background);
        if(neighbourMines!=0)
        {
            foreground.setTexture(TextureManager::GetTexture("number_" + to_string(neighbourMines)));
            foreground.setPosition(xPos*32,yPos*32);
            window->draw(foreground);
        }
    }

    if(lost == true && isMine)
    {
        background.setTexture(TextureManager::GetTexture("tile_revealed"));
        background.setPosition(xPos*32,yPos*32);
        window->draw(background);
        if(isFlagged)
            flag.setTexture(TextureManager::GetTexture("flag"));
        flag.setPosition(xPos*32,yPos*32);
        window->draw(flag);
        debugSprite.setTexture(TextureManager::GetTexture("mine"));
        debugSprite.setPosition(xPos*32,yPos*32);
        window->draw(debugSprite);
    }

    if( debugMode == true && isMine)
    {
        debugSprite.setTexture(TextureManager::GetTexture("mine"));
        debugSprite.setPosition(xPos*32,yPos*32);
        window->draw(debugSprite);
    }
}

void Tile::FLag()
{
    if(!isRevealed)
        isFlagged = !isFlagged;
}

void Tile::Reveal()
{
    if(isRevealed||isFlagged)
        return;
    else
        isRevealed = true;
}
