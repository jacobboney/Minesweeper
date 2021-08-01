//
// Created by jacob on 7/21/2021.
//

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include "TextureManager.h"


class Tile {
    //Variables
    bool hidden = true;
    bool mine = false;
    bool flag = false;
    short numOfNearbyMines;

    //Sprites
    sf::Sprite tileHidden;
    sf::Sprite tileRevealed;

    //Adjacent Tiles
    std::map<std::string, Tile*> adjacentTiles;

public:
    //Constructor
    Tile();

    //Mutators
    void setPosition(int x, int y);
    void setAdjacentTiles(std::string location, Tile* tile);
    void setMine();
    void setFlag();

    //Accessors
    sf::Sprite getTileSprite();
    bool getHiddenValue();
    bool getMineStatus();
    std::map<std::string, Tile*>& getAdjacentTiles();
    short getNumberOfNearbyMines();
    bool getFlagStatus();

    //Functions
    void drawTile(sf::RenderWindow& window);
    void revealTile();
    void increaseMineCounter();
    void deMine();
    void hideTile();
    void resetTile();
    void clear();

};


