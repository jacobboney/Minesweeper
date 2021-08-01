//
// Created by jacob on 7/21/2021.
//

#include "Tile.h"


//Constructor
Tile::Tile(){
    tileHidden.setTexture(TextureManager::GetTexture("tile_hidden"));
    tileRevealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    numOfNearbyMines = 0;
}

//Destructor

//Mutators
void Tile::setPosition(int x, int y){
    tileHidden.setPosition(x, y);
    tileRevealed.setPosition(x, y);
}
void Tile::setAdjacentTiles(std::string location, Tile* tile){
    adjacentTiles.emplace(location, tile);
}
void Tile::setMine(){
    mine = true;
}
void Tile::setFlag(){
    if(hidden == true){
        flag = !flag;
    }
}

//Accessors
sf::Sprite Tile::getTileSprite(){
    return tileHidden;
}
bool Tile::getHiddenValue(){
    return hidden;
}
bool Tile::getMineStatus(){
    return mine;
}
std::map<std::string, Tile*>& Tile::getAdjacentTiles(){
    return adjacentTiles;
}
short Tile::getNumberOfNearbyMines(){
    return numOfNearbyMines;
}
bool Tile::getFlagStatus(){
    return flag;
}

//Functions
void Tile::drawTile(sf::RenderWindow& window){
    if(hidden){
        window.draw(tileHidden);
        if(flag){
            sf::Sprite flag;
            flag.setTexture(TextureManager::GetTexture("flag"));
            flag.setPosition(tileHidden.getPosition().x, tileHidden.getPosition().y);
            window.draw(flag);
        }
    }
    else{
        window.draw(tileRevealed);
        if(flag){
            sf::Sprite flag;
            flag.setTexture(TextureManager::GetTexture("flag"));
            flag.setPosition(tileHidden.getPosition().x, tileHidden.getPosition().y);
            window.draw(flag);
        }
        if(hidden == false && mine == true){
            sf::Sprite mineSprite;
            mineSprite.setTexture(TextureManager::GetTexture("mine"));
            mineSprite.setPosition(tileRevealed.getPosition().x, tileRevealed.getPosition().y);
            window.draw(mineSprite);
        }
        else if (numOfNearbyMines != 0){
            std::string numberTile = "number_";
            numberTile+= std::to_string(numOfNearbyMines);
            sf::Sprite numberSprite;
            numberSprite.setTexture(TextureManager::GetTexture(numberTile));
            numberSprite.setPosition(tileRevealed.getPosition().x, tileRevealed.getPosition().y);
            window.draw(numberSprite);
        }
    }
}
void Tile::revealTile(){
    hidden = !hidden;

}
void Tile::increaseMineCounter(){
    numOfNearbyMines++;
}
void Tile::deMine(){
    mine = false;
}
void Tile::resetTile(){
    hidden = true;
    mine = false;
    flag = false;
    numOfNearbyMines = 0;
}
void Tile::clear(){
    std::map<std::string, Tile*>::iterator iter = adjacentTiles.begin();
    for(iter = adjacentTiles.begin(); iter != adjacentTiles.end(); iter++){
        delete iter->second;
    }
}

























