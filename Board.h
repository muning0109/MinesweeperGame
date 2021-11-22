#pragma once
#include "SFML/Graphics.hpp"
#include "Tile.h"
#include <vector>
using namespace std;
class Board{

    sf::Sprite test1, test2, test3, debug, smileyFace, sign, digits1, digits2, digits3;
    int width, height, numMines, numRevealed = 0, numFlagged = 0, numMineRemained;
    bool win = false, lost = false, debugMode = false;
public:
    vector<Tile> tiles;
    void LoadFile();
    Board(int w, int h, int numMines);
    map<int, int> generateMines();
    void CalculateAdjacentMines();
    void Draw(sf::RenderWindow* window);
    void Click(bool left, float x, float y);
    void LeftClick(int x, int y);
    void RevealNearby(int index);
    void Reset();
    void gameWon();
    void TestBoard(int boardNumber);
    map<int, int> LoadTestBoard(string filepath);
};