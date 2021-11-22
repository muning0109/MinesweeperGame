#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"


class GameManager{
    bool win;
    int width, height, numMines;


public:
    void LoadFile();
    void Run();
};