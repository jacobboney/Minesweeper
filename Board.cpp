//Jacob Boney
//COP 3503
//Project 03

#include "Board.h"

//Constructor
Board::Board(){
    config = Config();
    gameOver = false;
    tilesToWin = 0;
    tilesRevealed = 0;
    gameWin = false;
    numOfMines = 0;
    createTiles();
    setMines();
    createBoard();
    tileAwareness();

}

//Destructor
Board::~Board() {
    for(int i = 0; i < tiles.size(); i++){
        for(int j = 0; j < tiles.at(i).size(); j++){
            delete tiles[i][j];

        }
    }
}

//Mutators
void Board::setGameOver() {
    gameOver = !gameOver;

}
void Board::setGameWin() {
    gameWin = !gameWin;
}
void Board::setMines() {
    for(int i = 0; i < config.getMines(); i++){
        int tileToMineRow = Random::Int(0, (config.getRows() - 1));
        int tileToMineColumn = Random::Int(0, (config.getColumns() - 1));
        if(tiles[tileToMineRow][tileToMineColumn]->getMineStatus() == false){
            tiles[tileToMineRow][tileToMineColumn]->setMine();
        }
        else{
            if(i > -1){
                i--;
            }
        }
    }
    tilesToWin = config.getTiles() - config.getMines();
    numOfMines = config.getMines();
}
void Board::setMines(std::vector<std::vector<int>>* testBoardMines) {
    int numOfTestMines = 0;;
    for(int i = 0; i < tiles.size(); i++){
        for(int j = 0; j < tiles.at(i).size(); j++){
            if(testBoardMines->at(i).at(j) == 1){
                tiles[i][j]->setMine();
                numOfTestMines++;
            }
        }
    }
    tilesToWin = config.getTiles() - numOfTestMines;
    numOfMines = numOfTestMines;
    tileAwareness();
}
std::vector<std::vector<int>>* Board::setTestCase(std::string testNumber) {
    std::string testCase = "boards/testboard";
    testCase+= testNumber;
    testCase+= ".brd";
    std::ifstream inputFile(testCase);
    std::vector<std::vector<int>>* testBoardMines = new std::vector<std::vector<int>>;

    int mines = 0;
    int tempMineStorage;
    std::string tempStringStorage;
    while(std::getline(inputFile, tempStringStorage)){
        std::vector<int> tempMineVector;
        for(int i = 0; i < tempStringStorage.length(); i++){
            tempMineStorage = tempStringStorage[i] - 48;
            if(tempMineStorage == 1){
                mines++;
            }
            tempMineVector.push_back(tempMineStorage);
        }
        testBoardMines->push_back(tempMineVector);
    }
    return testBoardMines;

}
void Board::modifyNumOfMines(bool flagStatus, bool hiddenStatus) {
    if(flagStatus && hiddenStatus){
        numOfMines--;
    }
    else if (!flagStatus && hiddenStatus){
        numOfMines++;
    }
}

//Accessors
Config Board::accessConfig(){
    return config;
}
Tile* Board::accessTile(int row, int col) {
    return tiles[row][col];
}
std::map<std::string, sf::Sprite> &Board::getBoardSprites() {
    return boardSprites;
}
bool Board::gameStatus() {
    return gameOver;
}
bool Board::checkForWin() {
    if(tilesToWin == tilesRevealed){
        return true;
    }
    else{
        return false;
    }
}
void Board::displayMinesLeft(sf::RenderWindow& window) {
    int minesLeft = numOfMines;
    if(gameWin){
        minesLeft = 0;
        for(int i = 0; i < tiles.size(); i++){
            for(int j = 0; j < tiles.at(i).size(); j++){
                if(tiles[i][j]->getMineStatus() && !tiles[i][j]->getFlagStatus()){
                    tiles[i][j]->setFlag();
                }
            }
        }
    }
    if(minesLeft < 0){
        numberSprites.at(10).setPosition(0, config.getRows() * 32);
        window.draw(numberSprites.at(10));
    }
    if((abs(minesLeft) < 10 && abs(minesLeft) >= 0) /*|| (minesLeft > (-10) && minesLeft < 0)*/){
        int onesPlace = abs(minesLeft) % 10;
        int tensPlace = 0;
        int hundredsPlace = 0;
        combineNumbers(window, hundredsPlace, tensPlace, onesPlace);
    }
    else if((abs(minesLeft) <= 99 && abs(minesLeft) >= 10 ) /*|| (minesLeft >= (-99) && minesLeft <= (-10))*/){
        int onesPlace = abs(minesLeft) % 10;
        int tensPlace = (abs(minesLeft) / 10) % 10;
        int hundredsPlace = 0;
        combineNumbers(window, hundredsPlace, tensPlace, onesPlace);
    }
    else{
        int onesPlace = abs(minesLeft) % 10;
        int tensPlace = (abs(minesLeft) / 10) % 10;
        int hundredsPlace = (abs(minesLeft) / 100) % 10;
        combineNumbers(window, hundredsPlace, tensPlace, onesPlace);
    }
}

//Functions
void Board::createTiles() {

    for(int i = 0; i < accessConfig().getRows(); i++){
        std::vector<Tile*> tempTileVector;
        for(int j = 0; j < accessConfig().getColumns(); j++){
            Tile* tempTile;
            tempTile = new Tile;
            tempTileVector.push_back(tempTile);
        }
        tiles.push_back(tempTileVector);
    }

    int tileCounter = 0;
    for(int i = 0; i < tiles.size(); i++){
        for(int j = 0; j < tiles.at(i).size(); j++){
            tiles[i][j]->setPosition(j* 32,i* 32);
            tileCounter++;
        }
    }
}
void Board::drawTiles(sf::RenderWindow& window) {
    for(int i = 0; i < tiles.size(); i++){
        for(int j = 0; j < tiles.at(i).size(); j++){
            tiles[i][j]->drawTile(window);
        }
    }
}
void Board::drawBoard(sf::RenderWindow& window) {

    window.draw(face);
    window.draw(boardSprites.at("test1"));
    window.draw(boardSprites.at("test2"));
    window.draw(boardSprites.at("test3"));
    window.draw(boardSprites.at("debug"));


    if(!gameOver && !gameWin){
        window.draw(boardSprites.at("faceHappy"));
    }
    else if (gameWin){
        window.draw(boardSprites.at("faceWin"));
    }
    else{
        window.draw(boardSprites.at("faceLose"));
    }

}
void Board::createBoard() {
    //Declare Sprites
    sf::Sprite test1, test2, test3, debug, faceHappy, faceLose, faceWin, zero, one, two, three, four, five, six, seven, eight, nine, minus;

    //Tests
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.setPosition(config.getWidth() - 192, config.getRows()*32);
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.setPosition(config.getWidth() - 128, config.getRows()*32);
    test3.setTexture(TextureManager::GetTexture("test_3"));
    test3.setPosition(config.getWidth() - 64, config.getRows()*32);

    //Debug
    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition(config.getWidth() - 256, config.getRows()*32);

    //Faces
    faceHappy.setTexture(TextureManager::GetTexture("face_happy"));
    faceHappy.setPosition((config.getWidth() / 2) - 64, config.getRows()*32);
    faceLose.setTexture(TextureManager::GetTexture("face_lose"));
    faceLose.setPosition((config.getWidth() / 2) - 64, config.getRows()*32);
    faceWin.setTexture(TextureManager::GetTexture("face_win"));
    faceWin.setPosition((config.getWidth() / 2) - 64, config.getRows()*32);

    //Numbers
    //Adjusted the starting pixel for a few number so that they change more seamlessly
    zero.setTexture(TextureManager::GetTexture("digits"));
    zero.setTextureRect(sf::IntRect(0,0, 21,32));
    one.setTexture(TextureManager::GetTexture("digits"));
    one.setTextureRect(sf::IntRect(21,0, 21,32));
    two.setTexture(TextureManager::GetTexture("digits"));
    two.setTextureRect(sf::IntRect(43,0, 21,32));
    three.setTexture(TextureManager::GetTexture("digits"));
    three.setTextureRect(sf::IntRect(63,0, 21,32));
    four.setTexture(TextureManager::GetTexture("digits"));
    four.setTextureRect(sf::IntRect(84,0, 21,32));
    five.setTexture(TextureManager::GetTexture("digits"));
    five.setTextureRect(sf::IntRect(106,0, 21,32));
    six.setTexture(TextureManager::GetTexture("digits"));
    six.setTextureRect(sf::IntRect(127,0, 21,32));
    seven.setTexture(TextureManager::GetTexture("digits"));
    seven.setTextureRect(sf::IntRect(147,0, 21,32));
    eight.setTexture(TextureManager::GetTexture("digits"));
    eight.setTextureRect(sf::IntRect(169,0, 21,32));
    nine.setTexture(TextureManager::GetTexture("digits"));
    nine.setTextureRect(sf::IntRect(189,0, 21,32));
    minus.setTexture(TextureManager::GetTexture("digits"));
    minus.setTextureRect(sf::IntRect(210,0, 21,32));


    //Mapping Board Sprites
    boardSprites.emplace("test1", test1);
    boardSprites.emplace("test2", test2);
    boardSprites.emplace("test3", test3);
    boardSprites.emplace("debug", debug);
    boardSprites.emplace("faceHappy", faceHappy);
    boardSprites.emplace("faceLose", faceLose);
    boardSprites.emplace("faceWin", faceWin);

    //Mapping Number Sprites
    numberSprites.emplace(0, zero);
    numberSprites.emplace(1, one);
    numberSprites.emplace(2, two);
    numberSprites.emplace(3, three);
    numberSprites.emplace(4, four);
    numberSprites.emplace(5, five);
    numberSprites.emplace(6, six);
    numberSprites.emplace(7, seven);
    numberSprites.emplace(8, eight);
    numberSprites.emplace(9, nine);
    numberSprites.emplace(10, minus);
}
void Board::drawDebug(sf::RenderWindow& window) {
        for (int i = 0; i < tiles.size(); i++) {
            for (int j = 0; j < tiles.at(i).size(); j++) {
                if (tiles[i][j]->getMineStatus()) {
                    sf::Sprite tempMine;
                    tempMine.setTexture(TextureManager::GetTexture("mine"));
                    tempMine.setPosition(tiles[i][j]->getTileSprite().getPosition().x,
                                         tiles[i][j]->getTileSprite().getPosition().y);
                    window.draw(tempMine);
                }
            }
        }
}
void Board::tileAwareness() {
    for(int i = 0; i < tiles.size(); i++){
        for(int j = 0; j < tiles.at(i).size(); j++){
            if(i == 0 || j == 0){
                tiles[i][j]->setAdjacentTiles( "topLeft", nullptr);
            }
            else{
                tiles[i][j]->setAdjacentTiles("topLeft", tiles[i - 1][j - 1]);
                if(tiles[i - 1][j - 1]->getMineStatus()){
                    tiles[i][j]->increaseMineCounter();
                }
            }
            if(i == 0){
                tiles[i][j]->setAdjacentTiles("topMiddle", nullptr);
            }
            else{
                tiles[i][j]->setAdjacentTiles("topMiddle", tiles[i - 1][j]);
                if(tiles[i - 1][j]->getMineStatus()){
                    tiles[i][j]->increaseMineCounter();
                }
            }
            if(i == 0 || j == config.getColumns() - 1){
                tiles[i][j]->setAdjacentTiles("topRight", nullptr);
            }
            else{
                tiles[i][j]->setAdjacentTiles("topRight", tiles[i - 1][j + 1]);
                if(tiles[i - 1][j + 1]->getMineStatus()){
                    tiles[i][j]->increaseMineCounter();
                }
            }
            if(j == 0){
                tiles[i][j]->setAdjacentTiles("middleLeft", nullptr);
            }
            else{
                tiles[i][j]->setAdjacentTiles("middleLeft", tiles[i][j - 1]);
                if(tiles[i][j - 1]->getMineStatus()){
                    tiles[i][j]->increaseMineCounter();
                }
            }
            if(j == config.getColumns() - 1){
                tiles[i][j]->setAdjacentTiles("middleRight", nullptr);
            }
            else{
                tiles[i][j]->setAdjacentTiles("middleRight", tiles[i][j + 1]);
                if(tiles[i][j + 1]->getMineStatus()){
                    tiles[i][j]->increaseMineCounter();
                }
            }
            if(i == config.getRows() - 1 || j == 0){
                tiles[i][j]->setAdjacentTiles("bottomLeft", nullptr);
            }
            else{
                tiles[i][j]->setAdjacentTiles("bottomLeft", tiles[i + 1][j - 1]);
                if(tiles[i + 1][j - 1]->getMineStatus()){
                    tiles[i][j]->increaseMineCounter();
                }
            }
            if(i == config.getRows() - 1){
                tiles[i][j]->setAdjacentTiles("bottomMiddle", nullptr);
            }
            else{
                tiles[i][j]->setAdjacentTiles("bottomMiddle", tiles[i + 1][j]);
                if(tiles[i + 1][j]->getMineStatus()){
                    tiles[i][j]->increaseMineCounter();
                }
            }
            if(i == config.getRows() - 1 || j == config.getColumns() - 1){
                tiles[i][j]->setAdjacentTiles("bottomRight", nullptr);
            }
            else{
                tiles[i][j]->setAdjacentTiles("bottomRight", tiles[i + 1][j + 1]);
                if(tiles[i + 1][j + 1]->getMineStatus()){
                    tiles[i][j]->increaseMineCounter();
                }
            }

        }
    }
}
void Board::recursiveTileReveal(Tile* tile) {
    if(tile == nullptr){
        return;
    }
    else if(!tile->getHiddenValue() || tile->getFlagStatus()){
        return;
    }
    else if (tile->getNumberOfNearbyMines() > 0){
        tile->revealTile();
        tilesRevealed++;
        return;
    }
    else{
        tile->revealTile();
        std::map<std::string, Tile*>::iterator iter = tile->getAdjacentTiles().begin();
        for(iter = tile->getAdjacentTiles().begin(); iter != tile->getAdjacentTiles().end(); iter++){
            recursiveTileReveal(iter->second);
        }
        tilesRevealed++;
        return;
    }
}
void Board::revealTile(Tile* tile) {
    if(tile->getNumberOfNearbyMines() > 0){
        if(!tile->getFlagStatus()) {
            tile->revealTile();
            tilesRevealed++;
        }
    }
    else{
        recursiveTileReveal(tile);
    }
}
void Board::deMineBoard() {
    tilesRevealed = 0;
    for(int i = 0; i < tiles.size(); i++){
        for(int j = 0; j < tiles.at(i).size(); j++){
            tiles[i][j]->resetTile();
        }
    }
}
void Board::combineNumbers(sf::RenderWindow& window, int hundredsPlace, int tensPlace, int onesPlace) {
    for(int i = 0; i < 3; i++){
        numberSprites.at(hundredsPlace).setPosition(21, config.getRows() * 32);
        window.draw(numberSprites.at(hundredsPlace));
        numberSprites.at(tensPlace).setPosition(42, config.getRows() * 32);
        window.draw(numberSprites.at(tensPlace));
        numberSprites.at(onesPlace).setPosition(63, config.getRows() * 32);
        window.draw(numberSprites.at(onesPlace));
    }
}

































