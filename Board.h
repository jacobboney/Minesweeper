//Jacob Boney
//COP 3503
//Project 03

#pragma once
#include <vector>
#include "Config.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include "Random.h"
#include <fstream>
#include <string>
#include <iostream>

class Board {
    //Variables
    bool gameOver;
    int tilesToWin;
    int tilesRevealed;
    bool gameWin;
    int numOfMines;

    //Config
    Config config;

    //Tiles
    std::vector<std::vector<Tile*>> tiles;

    //Sprites
    std::map<std::string, sf::Sprite> boardSprites;
    std::map<int, sf::Sprite> numberSprites;
    sf::Sprite face;

public:

    //Constructor
    Board();

    //Destructor
    ~Board();

    //Mutators
    void setGameOver();
    void setGameWin();
    void setMines();
    void setMines(std::vector<std::vector<int>>* testBoardMines);
    std::vector<std::vector<int>>* setTestCase(std::string testNumber);
    void modifyNumOfMines(bool flagStatus, bool hiddenStatus);

    //Accessors
    Config accessConfig();
    Tile* accessTile(int row, int col);
    std::map<std::string, sf::Sprite>& getBoardSprites();
    bool gameStatus();
    bool checkForWin();
    void displayMinesLeft(sf::RenderWindow& window);


    //Functions
    void createTiles();
    void drawTiles(sf::RenderWindow& window);
    void drawBoard(sf::RenderWindow& window);
    void createBoard();
    void drawDebug(sf::RenderWindow& window);
    void tileAwareness();
    void recursiveTileReveal(Tile* tile);
    void revealTile(Tile* tile);
    void deMineBoard();
    void combineNumbers(sf::RenderWindow& window, int hundredsPlace, int tensPlace, int onesPlace);
};



