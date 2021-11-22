#include "Board.h"
#include <iostream>
#include "Tile.h"
#include "map"
#include "Random.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "fstream"


Board::Board(int w, int h, int numMines)
{
    width = w;
    height = h;
    this->numMines = numMines;
    numMineRemained = numMines;
    map<int, int> randomMinesNum = generateMines();
    map<int, bool> randomMines;
    for(int i = 0; i < width*height; i++)
    {
        if (randomMinesNum[i] == 1)
            randomMines[i] = true;
        else
            randomMines[i] = false;
    }
    for(int i = 0; i < width*height; i++)
    {
        Tile temp(randomMines[i],i, width, height);
        tiles.push_back(temp);
    }
    CalculateAdjacentMines();
}

map<int, int> Board::generateMines()
{
    map<int, int> randomMines;
    for(int i = 0; i < width*height; i++)
    {
        randomMines[i] = 0;
    }
    int generated = 0;
    while(generated < this->numMines)
    {
        int random = Random::Int(0,height*width);
        if (randomMines[random] == 0)
        {
            randomMines[random] = 1;
            generated++;
        }
    }
    return randomMines;
}

void Board::CalculateAdjacentMines()
{
    for(int i = 0; i < tiles.size(); i++)
    {
            if(i < width-1 && i!= 0)
            {
                if(tiles[i-1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-1+width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+1+width].isMine)
                    tiles[i].neighbourMines++;
            } else if( i> width*(height-1) && i < width*height-1)
            {
                if(tiles[i-1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-1-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+1-width].isMine)
                    tiles[i].neighbourMines++;
            } else if( i%width == 0 && i!=0 && i!= width*(height-1))
            {
                if(tiles[i-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-width+1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width+1].isMine)
                    tiles[i].neighbourMines++;
            } else if( i%width == (width-1) && i!=width-1 && i!= width*height-1)
            {
                if(tiles[i-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-width-1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width-1].isMine)
                    tiles[i].neighbourMines++;
            } else if(i==0)
            {
                if(tiles[i+1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width+1].isMine)
                    tiles[i].neighbourMines++;
            } else if(i==width-1)
            {
                if(tiles[i-1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width-1].isMine)
                    tiles[i].neighbourMines++;
            } else if(i==width*(height-1))
            {
                if(tiles[i+1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-width+1].isMine)
                    tiles[i].neighbourMines++;
            } else if(i==width*height-1)
            {
                if(tiles[i-1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-width-1].isMine)
                    tiles[i].neighbourMines++;
            } else {
                if(tiles[i-1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+1].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-1-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+1-width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i-1+width].isMine)
                    tiles[i].neighbourMines++;
                if(tiles[i+1+width].isMine)
                    tiles[i].neighbourMines++;
            }

    }
}

void Board::Draw(sf::RenderWindow* window)
{
    for( int i = 0; i < tiles.size(); i++)
    {
        tiles[i].Draw(window, debugMode, lost, win);
    }
    if(win == true)
    {
        for( int i = 0; i < tiles.size(); i++)
        {
            if(!tiles[i].isRevealed && tiles[i].isMine)
            {
                tiles[i].flag.setTexture(TextureManager::GetTexture("flag"));
                tiles[i].flag.setPosition(tiles[i].xPos*32,tiles[i].yPos*32);
                window->draw(tiles[i].flag);
            }
        }
    }
    if(win == true)
        smileyFace.setTexture(TextureManager::GetTexture("face_win"));
    else if(lost)
        smileyFace.setTexture(TextureManager::GetTexture("face_lose"));
    else
        smileyFace.setTexture(TextureManager::GetTexture("face_happy"));
    smileyFace.setPosition(16*(width-2),height*32);
    window->draw(smileyFace);
    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition(16*(width+6),height*32);
    window->draw(debug);
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.setPosition(16*(width+10),height*32);
    window->draw(test1);
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.setPosition(16*(width+14),height*32);
    window->draw(test2);
    test3.setTexture(TextureManager::GetTexture("test_3"));
    test3.setPosition(16*(width+18),height*32);
    window->draw(test3);
    //numMineRemained = numMines - numFlagged;
    digits1.setTexture(TextureManager::GetTexture("digits"));
    digits1.setTextureRect(sf::IntRect((abs(numMineRemained/100))*21, 0, 21, 32));
    digits1.setPosition(21,height*32);
    window->draw(digits1);
    digits2.setTexture(TextureManager::GetTexture("digits"));
    digits2.setTextureRect(sf::IntRect(abs((numMineRemained%100)/10)*21, 0, 21, 32));
    digits2.setPosition(42,height*32);
    window->draw(digits2);
    digits3.setTexture(TextureManager::GetTexture("digits"));
    digits3.setTextureRect(sf::IntRect((abs(numMineRemained%100)%10)*21, 0, 21, 32));
    digits3.setPosition(63,height*32);
    window->draw(digits3);
    if(numMineRemained < 0)
    {
        sign.setTexture(TextureManager::GetTexture("digits"));
        sign.setTextureRect(sf::IntRect(210,0,21,32));
        sign.setPosition(0,height*32);
        window->draw(sign);
    }
}

void Board::Click(bool left, float x, float y)
{
    int xPos = (int)x /32;
    int yPos = (int)y /32;
    if (!left && y < height*32)
    {

        if(win || lost)
        {
            return;
        }
        if(!tiles[yPos*width+xPos].isRevealed)
        {
            if(tiles[yPos*width+xPos].isFlagged)
            {
                numFlagged--;
                numMineRemained++;
            }

            else
            {
                numMineRemained--;
                numFlagged++;
                gameWon();
            }

        }
        tiles[yPos*width+xPos].FLag();
        //cout << win << endl;
        gameWon();
    } else if(left && y < height*32)
    {
        if(tiles[yPos*width+xPos].isMine)
        {
            lost = true;
            return;
        }
        LeftClick(xPos,yPos);
        gameWon();
    } else if (left && x > 16*(width-2) && x < 16*(width+2) && y > height*32 && y < (height+2)*32 ){
        Reset();
    } else if (left && x > 16*(width+6) && x < 16*(width+10) && y > height*32 && y < (height+2)*32)
    {
        if(win || lost)
        {
            return;
        }
        debugMode = !debugMode;
    } else if (left && x > 16*(width+10) && x < 16*(width+14) && y > height*32 && y < (height+2)*32){
        TestBoard(1);
    } else if (left && x > 16*(width+14) && x < 16*(width+18) && y > height*32 && y < (height+2)*32){
        TestBoard(2);
    } else if (left && x > 16*(width+18) && x < 16*(width+22) && y > height*32 && y < (height+2)*32){
        TestBoard(3);
    }
    gameWon();

}

void Board::LeftClick(int x, int y)
{
    int index = y*width+x;
    Tile* tile = &tiles[index];
    if(!tiles[index].isFlagged && !tiles[index].isRevealed && !lost)
        numRevealed++;
    if(win || lost)
    {
        return;
    }
    if(tile->neighbourMines == 0 && !tile->isFlagged && !tile->isMine && !tile->isRevealed)
    {
        tile->Reveal();
        RevealNearby(index);
    }else{
        tile->Reveal();
    }

}

void Board::RevealNearby(int index)
{
    int row = index/width;
    int column = index%width;
        if(row > 0 )
        {
            LeftClick(column,row-1);
        }
        if(row < height-1)
        {
            LeftClick(column,row+1);
        }
        if(column > 0)
        {
            LeftClick(column-1,row);
        }
        if(column < width-1)
        {
            LeftClick(column+1,row);
        }
        if(row > 0 && column > 0)
        {
            LeftClick(column-1,row-1);
        }
        if(row < height-1 && column > 0)
        {
            LeftClick(column-1,row+1);
        }
        if(row > 0 && column < width-1)
        {
            LeftClick(column+1,row-1);
        }

        if(row < height-1 && column < width-1)
        {
            LeftClick(column+1,row+1);
        }

}


void Board::Reset()
{
    LoadFile();
    for (int i  = 0; i < width*height; i++)
    {
        tiles.clear();
    }
    map<int, int> randomMinesNum = generateMines();
    map<int, bool> randomMines;
    for(int i = 0; i < width*height; i++)
    {
        if (randomMinesNum[i] == 1)
            randomMines[i] = true;
        else
            randomMines[i] = false;
    }
    for(int i = 0; i < width*height; i++)
    {
        Tile temp(randomMines[i],i, width, height);
        tiles.push_back(temp);
    }
    
    CalculateAdjacentMines();
    win = false;
    lost = false;
    numRevealed = 0;
    numFlagged = 0;
    numMineRemained = numMines;
}

void Board::gameWon()
{
    int count = 0;
    for (int i  = 0; i < width*height; i++)
    {
        if(!tiles[i].isMine && tiles[i].isRevealed)
            count++;
    }
    if(count == (width*height-numMines))
    {
        win = true;
        numMineRemained = 0;
    }

    else
        win = false;

}

void Board::TestBoard(int boardNumber)
{
    numMines = 0;
    for (int i  = 0; i < width*height; i++)
    {
        tiles.clear();
    }

    map<int, int> randomMinesNum = LoadTestBoard("boards/testboard"+to_string(boardNumber)+".brd");
    map<int, bool> randomMines;
    for(int i = 0; i < width*height; i++)
    {
        if (randomMinesNum[i] == 1)
        {
            randomMines[i] = true;
            numMines++;
        }
        else
            randomMines[i] = false;
    }
    for(int i = 0; i < width*height; i++)
    {
        Tile temp(randomMines[i],i, width, height);
        tiles.push_back(temp);
    }
    /*for(int i = 0; i < tiles.size(); i++)
    {
        if(i%width == 0)
            cout << endl;
        cout << tiles[i].isMine;
    }
    cout << endl;*/
    CalculateAdjacentMines();
    win = false;
    lost = false;
    numRevealed = 0;
    numFlagged = 0;
    numMineRemained = numMines;

}

map<int, int> Board::LoadTestBoard(string filepath)
{
    fstream boardFile;
    boardFile.open(filepath, ios::in);
    map<int, int> mines;
    string row;
    int count = 0;
    for( int i = 0; i < height; i++)
    {
        getline(boardFile, row);
        for(int j = 0; j < width; j++)
        {
            int mine = stoi(row.substr(j, 1));
            mines[count] = mine;
            count++;
        }
    }

    return mines;
}

void Board::LoadFile()
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