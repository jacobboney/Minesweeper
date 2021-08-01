//Jacob Boney
//COP 3503
//Project 03

#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>



class Config {

    //Config Variables
    int numOfColumns;
    int numOfRows;
    int numOfMines;

    //Window Settings
    int windowWidth;
    int windowHeight;
    int numOfTiles;

public:

    //Constructor
    Config();

    //Load Config file from folder
    void loadConfig();

    //Mutators
    void setColumns(int columns);
    void setRows(int rows);
    void setNumOfMines(int mines);
    void setWindowWidth();
    void setWindowHeight();
    void setNumOfTiles();

    //Accessors
    int getColumns();
    int getRows();
    int getWidth();
    int getHeight();
    int getMines();
    int getTiles();

};



