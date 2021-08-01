#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Tile.h"
#include "Board.h"

//Functions for Main

//Checks for and responds to a left mouse click
void checkForLeftClick(sf::Event& event, sf::RenderWindow& window, Board& board, bool& debug);
//Checks for and responds to a right mouse click
void checkForRightClick(sf::Event& event, sf::RenderWindow& window, Board& board);
//When called updates the window to reflect any changes
void updateWindow(sf::RenderWindow& window, Board& board, bool& debug);


int main()
{
    //Opens and set parameters for window based on config file
    Board board = Board();
    //Toggle for debug mode
    bool debug = false;

    //Creates window based on values from config file
    sf::RenderWindow window(sf::VideoMode(board.accessConfig().getWidth(), board.accessConfig().getHeight()), "Minesweeper");
    //Sets frame limit to 30FPS to reduce load on CPU/GPU (less resources needed)
    window.setFramerateLimit(30);

    //Main window loop
    while (window.isOpen())
    {
        sf::Event event;
        //Checks for and event in the window
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                checkForLeftClick(event, window, board, debug);
                checkForRightClick(event, window,board);

            }
        }
        updateWindow(window, board, debug);
    }

    return 0;
}


void updateWindow(sf::RenderWindow &window, Board &board, bool &debug) {
    for (int i = 0; i < 2; i++) {
        window.clear(sf::Color(255, 255, 255));
        board.drawTiles(window);
        board.drawBoard(window);
        board.displayMinesLeft(window);
        if (debug) {
            board.drawDebug(window);
        }


        window.display();
    }
}

void checkForLeftClick(sf::Event &event, sf::RenderWindow &window, Board &board, bool &debug) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        //Branch executes if game is lost
        if (board.gameStatus()) {

            //Starts a new game if the losing face is clicked
            if (board.getBoardSprites().at("faceLose").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameOver();
                board.deMineBoard();
                board.setMines();
                board.tileAwareness();
            }

            //Enables-Disables debug button is clicked
            else if (board.getBoardSprites().at("debug").getGlobalBounds().contains(mousePosition.x,
                                                                                      mousePosition.y)) {
                if (board.checkForWin() == false && board.gameStatus() == false) {
                    debug = !debug;
                }
            }

            //Loads Test Board 1 if button is clicked
            else if (board.getBoardSprites().at("test1").getGlobalBounds().contains(mousePosition.x,
                                                                                      mousePosition.y)) {
                board.setGameOver();
                board.deMineBoard();
                board.setMines(board.setTestCase("1"));

            }

            //Loads Test Board 2 if button is clicked
            else if (board.getBoardSprites().at("test2").getGlobalBounds().contains(mousePosition.x,
                                                                                      mousePosition.y)) {
                board.setGameOver();
                board.deMineBoard();
                board.setMines(board.setTestCase("2"));
            }

            //Loads Test Board 3 if button is clicked
            else if (board.getBoardSprites().at("test3").getGlobalBounds().contains(mousePosition.x,
                                                                                      mousePosition.y)) {
                board.setGameOver();
                board.deMineBoard();
                board.setMines(board.setTestCase("3"));
            }
        }
        //Branch executes if game is won
        else if (board.checkForWin()) {

            //Starts a new game is the win face is clicked
            if (board.getBoardSprites().at("faceWin").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameWin();
                board.deMineBoard();
                board.setMines();
                board.tileAwareness();
            }

            //Enables-Disables debug mode
            else if (board.getBoardSprites().at("debug").getGlobalBounds().contains(mousePosition.x,
                                                                                      mousePosition.y)) {
                if (board.checkForWin() == false && board.gameStatus() == false) {
                    debug = !debug;
                }
            }

            //Loads Test Board 1 if button is clicked
            else if (board.getBoardSprites().at("test1").getGlobalBounds().contains(mousePosition.x,
                                                                                      mousePosition.y)) {
                board.setGameWin();
                board.deMineBoard();
                board.setMines(board.setTestCase("1"));
            }

            //Loads Test Board 2 if button is clicked
            else if (board.getBoardSprites().at("test2").getGlobalBounds().contains(mousePosition.x,
                                                                                      mousePosition.y)) {
                board.setGameWin();
                board.deMineBoard();
                board.setMines(board.setTestCase("2"));
            }

            //Loads Test Board 3 if button is clicked
            else if (board.getBoardSprites().at("test3").getGlobalBounds().contains(mousePosition.x,
                                                                                      mousePosition.y)) {
                board.setGameWin();
                board.deMineBoard();
                board.setMines(board.setTestCase("3"));
            }
        }

        //Branch executes while game is still ongoing
        else {

            //Check if a tiles is clicked
            for (int i = 0; i < board.accessConfig().getRows(); i++) {
                for (int j = 0; j < board.accessConfig().getColumns(); j++) {
                    if (board.accessTile(i, j)->getTileSprite().getGlobalBounds().contains(mousePosition.x,
                                                                                           mousePosition.y) &&
                        board.accessTile(i, j)->getHiddenValue() && !board.accessTile(i, j)->getFlagStatus()) {
                        if (board.accessTile(i, j)->getMineStatus()) {
                            for (int k = 0; k < board.accessConfig().getRows(); k++) {
                                for (int l = 0; l < board.accessConfig().getColumns(); l++) {
                                    if (board.accessTile(k, l)->getMineStatus()) {
                                        board.accessTile(k, l)->revealTile();
                                    }
                                }
                            }
                            board.setGameOver();
                        } else {
                            board.revealTile(board.accessTile(i, j));
                            if (board.checkForWin()) {
                                board.setGameWin();
                            }
                        }
                    }
                }
            }

            //Enables-Disables debug mode
            if (board.getBoardSprites().at("debug").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                if (board.checkForWin() == false && board.gameStatus() == false) {
                    debug = !debug;
                }
            }

            //Starts new game is happy face is clicked
            if (board.getBoardSprites().at("faceHappy").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.deMineBoard();
                board.setMines();
                board.tileAwareness();
            }

            //Loads Test Board 1 if button is clicked
            if (board.getBoardSprites().at("test1").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.deMineBoard();
                board.setMines(board.setTestCase("1"));
            }

            //Loads Test Board 2 if button is clicked
            if (board.getBoardSprites().at("test2").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.deMineBoard();
                board.setMines(board.setTestCase("2"));
            }

            //Loads Test Board 3 if button is clicked
            if (board.getBoardSprites().at("test3").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.deMineBoard();
                board.setMines(board.setTestCase("3"));
            }
        }
    }
}

void checkForRightClick(sf::Event &event, sf::RenderWindow &window, Board &board) {
    if (event.mouseButton.button == sf::Mouse::Right) {
        if (!board.checkForWin() && !board.gameStatus()) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            //Sets Flag if tile is clicked and it is still hidden
            for (int i = 0; i < board.accessConfig().getRows(); i++) {
                for (int j = 0; j < board.accessConfig().getColumns(); j++) {
                    if (board.accessTile(i, j)->getTileSprite().getGlobalBounds().contains(mousePosition.x,
                                                                                           mousePosition.y)) {
                        board.accessTile(i, j)->setFlag();
                        board.modifyNumOfMines(board.accessTile(i, j)->getFlagStatus(),
                                               board.accessTile(i, j)->getHiddenValue());
                    }
                }
            }
        }
    }
}



