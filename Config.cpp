//Jacob Boney
//COP 3503
//Project 03
#include "Config.h"

//Constructor
Config::Config(){
    loadConfig();
}


//Loads Configuration File
void Config::loadConfig() {
    std::ifstream configInput("boards/config.cfg");
    if(configInput.is_open()){
        std::string tempInputStream;
        //Get&Set Columns
        std::getline(configInput, tempInputStream);
        setColumns(stoi(tempInputStream));
        setWindowWidth();
        //Get&Set Rows
        std::getline(configInput, tempInputStream);
        setRows(stoi(tempInputStream));
        setWindowHeight();
        setNumOfTiles();
        //Get&Set Mines
        std::getline(configInput, tempInputStream);
        setNumOfMines(stoi(tempInputStream));
    }
}

//Mutators
void Config::setColumns(int columns) {
    numOfColumns = columns;
}
void Config::setRows(int rows) {
    numOfRows = rows;
}
void Config::setNumOfMines(int mines) {
    numOfMines = mines;
}
void Config::setWindowWidth(){
    windowWidth = (getColumns() * 32);
}
void Config::setWindowHeight(){
    windowHeight = ((getRows() * 32) + 88);
}
void Config::setNumOfTiles(){
    numOfTiles = (getColumns() * getRows());
}

//Accessors
int Config::getColumns(){
    return numOfColumns;
}
int Config::getRows(){
    return numOfRows;
}
int Config::getWidth() {
    return windowWidth;
}
int Config::getHeight() {
    return windowHeight;
}
int Config::getMines() {
    return numOfMines;
}
int Config::getTiles() {
    return numOfTiles;
}



