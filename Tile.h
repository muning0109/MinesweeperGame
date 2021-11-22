#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include <vector>
using namespace std;
struct Tile{
    sf::Sprite foreground, background, flag, debugSprite;
    bool isMine, isFlagged, isRevealed;
    int neighbourMines;
    Tile* upLeft;
    Tile* up;
    Tile* upRight;
    Tile* right;
    Tile* bottomRight;
    Tile* bottom;
    Tile* bottomLeft;
    Tile* left;
    int xPos = 0, yPos = 0;
public:
    Tile( bool isMine, int i, int width, int height);
    void FLag();
    void Reveal();
    void Draw(sf::RenderWindow *window, bool debugMode, bool lost, bool win);
};