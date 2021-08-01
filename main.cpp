#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Tile.h"
#include "Board.h"

void checkForLeftClick(sf::Event& event, sf::RenderWindow& window, Board& board, bool& debug);
void checkForRightClick(sf::Event& event, sf::RenderWindow& window, Board& board);
void updateWindow(sf::RenderWindow& window, Board& board, bool& debug);


int main()
{
    //Opens and set parameters for window based on config file
    Board board = Board();
    bool debug = false;

    //Creates window based on values from config file
    sf::RenderWindow window(sf::VideoMode(board.accessConfig().getWidth(), board.accessConfig().getHeight()), "Minesweeper");
    window.setFramerateLimit(30);
    while (window.isOpen())
    {
        sf::Event event;
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

void updateWindow(sf::RenderWindow& window, Board& board, bool& debug){
    for(int i = 0; i < 2; i++) {
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

void checkForLeftClick(sf::Event& event, sf::RenderWindow& window, Board& board, bool& debug) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (board.gameStatus()) {
            if (board.getBoardSprites().at("faceLose").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameOver();
                board.deMineBoard();
                board.setMines();
                board.tileAwareness();
            }
            else if (board.getBoardSprites().at("debug").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                if(board.checkForWin() == false && board.gameStatus() == false) {
                    debug = !debug;
                }
            }
            else if (board.getBoardSprites().at("test1").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameOver();
                board.deMineBoard();
                board.setMines(board.setTestCase("1"));

            }
            else if (board.getBoardSprites().at("test2").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameOver();
                board.deMineBoard();
                board.setMines(board.setTestCase("2"));
            }
            else if (board.getBoardSprites().at("test3").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameOver();
                board.deMineBoard();
                board.setMines(board.setTestCase("3"));
            }
        }
        else if (board.checkForWin()) {
            if (board.getBoardSprites().at("faceWin").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameWin();
                board.deMineBoard();
                board.setMines();
                board.tileAwareness();
            }
            else if (board.getBoardSprites().at("debug").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                if(board.checkForWin() == false && board.gameStatus() == false) {
                    debug = !debug;
                }
            }
            else if (board.getBoardSprites().at("test1").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameWin();
                board.deMineBoard();
                board.setMines(board.setTestCase("1"));
            }
            else if (board.getBoardSprites().at("test2").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameWin();
                board.deMineBoard();
                board.setMines(board.setTestCase("2"));
            }
            else if (board.getBoardSprites().at("test3").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.setGameWin();
                board.deMineBoard();
                board.setMines(board.setTestCase("3"));
            }
        }
        else {
            for (int i = 0; i < board.accessConfig().getRows(); i++) {
                for (int j = 0; j < board.accessConfig().getColumns(); j++) {
                    if (board.accessTile(i, j)->getTileSprite().getGlobalBounds().contains(mousePosition.x,
                                                                                           mousePosition.y) &&
                        board.accessTile(i, j)->getHiddenValue() && !board.accessTile(i,j)->getFlagStatus()) {
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
                            if(board.checkForWin()){
                                board.setGameWin();
                            }
                        }

                    }
                }
            }
            if (board.getBoardSprites().at("debug").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                if(board.checkForWin() == false && board.gameStatus() == false) {
                    debug = !debug;
                }
            }
            if (board.getBoardSprites().at("faceHappy").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.deMineBoard();
                board.setMines();
                board.tileAwareness();
            }
            if (board.getBoardSprites().at("test1").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.deMineBoard();
                board.setMines(board.setTestCase("1"));
            }
            if (board.getBoardSprites().at("test2").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.deMineBoard();
                board.setMines(board.setTestCase("2"));
            }
            if (board.getBoardSprites().at("test3").getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                board.deMineBoard();
                board.setMines(board.setTestCase("3"));
            }
        }
    }
}

void checkForRightClick(sf::Event &event, sf::RenderWindow &window, Board& board) {
    if (event.mouseButton.button == sf::Mouse::Right) {
        if (!board.checkForWin() && !board.gameStatus()) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            for (int i = 0; i < board.accessConfig().getRows(); i++) {
                for (int j = 0; j < board.accessConfig().getColumns(); j++) {
                    if (board.accessTile(i, j)->getTileSprite().getGlobalBounds().contains(mousePosition.x,
                                                                                           mousePosition.y)) {
                        board.accessTile(i, j)->setFlag();
                        board.modifyNumOfMines(board.accessTile(i,j)->getFlagStatus(), board.accessTile(i,j)->getHiddenValue());
                    }
                }
            }
        }
    }
}



