#include "game.hpp"
#include <iostream>

Game::Game()
    : mAi('O'),
      mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TicTacToeMiniMax") {
  auto windowPosition = getScreenSize() - mWindow.getSize();
  mWindow.setPosition(sf::Vector2i(windowPosition.x / 2, windowPosition.y / 2));
  loadTextures();
  loadFonts();
}

void Game::run() {
  while (mWindow.isOpen()) {
    updatePhase();
    if(mDraw){
      renderingPhase();
      mDraw = false;
    }
  }
}

void Game::newGame(bool multiPlayer)
{
  mBoard.clear();
  mStatus = Status::PLAYING;
  mIsXTurn = true;
  mMultiplayer = multiPlayer;
  if(!multiPlayer){
    mAi.setAiPlayer('O');
  }
  mDraw = true;
}

void Game::updatePhase() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      mWindow.close();
    }
    if (event.type == sf::Event::KeyReleased) {
      switch (event.key.code) {
        case sf::Keyboard::Return:
          break;
        case sf::Keyboard::N:
          newGame(true);
          break;
        case sf::Keyboard::M:
          newGame(false);
          break;
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
          mWindow.close();
          break;
        default:
          break;
      }
    }
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Button::Left) {
        if(mStatus == Status::PLAYING){
            int row = event.mouseButton.y / CELL_SIZE;
            int col = event.mouseButton.x / CELL_SIZE;
            bool moveAccepted = mBoard.tryToMakeMove(row, col, mIsXTurn ? 'X' : 'O');
            if(moveAccepted){
                if(mIsXTurn){
                  if(mBoard.checkForAVictory('X')){
                    std::cout << "X won!!!" << std::endl;
                    mStatus = Status::X_WON;
                  }
                } else {
                  if(mBoard.checkForAVictory('O')){
                    std::cout << "O won!!!" << std::endl;
                    mStatus = Status::O_WON;
                  }
                }

                if(mMultiplayer){
                    if(mStatus == Status::PLAYING){
                      mIsXTurn = !mIsXTurn;
                    }
                } else {
                    mAi.makeMove(this->mBoard);
                    if(mBoard.checkForAVictory('O')){
                      std::cout << "AI won!!!" << std::endl;
                      mStatus = Status::O_WON;
                    }
                }
                if(mStatus == Status::PLAYING && mBoard.checkIfGameOver()){
                   mStatus = Status::TIE;
                   std::cout << "Tie!!!" << std::endl;
                }

            } else {
              std::cout << "Illegal move" << std::endl;
            }
            mDraw = true;
        }
    }
  }
}

void Game::renderingPhase() {
  mWindow.clear(sf::Color::White);
  renderBoard();
  renderGameStatus();
  mWindow.display();
}

void Game::renderBoard()
{
  sf::Sprite background;
  background.setTexture(mTextureManager.get(TextureID::Board));
  background.setPosition(0, 0);
  mWindow.draw(background);
  auto grid = mBoard.grid();
  for(size_t row{0u}; row < grid.size(); ++row){
      for(size_t col{0u}; col < grid[row].size(); ++col){
        if(grid[row][col] == ' '){
            continue;
        }
        sf::Sprite spot;
        spot.setPosition(col * CELL_SIZE, row * CELL_SIZE);
        if(grid[row][col] == 'X'){
          spot.setTexture(mTextureManager.get(TextureID::BlueX));
        } else if(grid[row][col] == 'O'){
          spot.setTexture(mTextureManager.get(TextureID::RedO));
        }
        mWindow.draw(spot);
      }
  }
}

void Game::renderGameStatus()
{
  sf::Text text(mStatusText[mStatus], mFontManager.get(FontID::GameStatus), 100);
  text.setColor(sf::Color(0,127,0));
  auto textWidth = text.getGlobalBounds().width;
  auto textHeight = text.getGlobalBounds().height;
  text.setPosition((WINDOW_WIDTH - textWidth) / 2,
                   (WINDOW_HEIGHT - textHeight) / 2 - textHeight / 2);
  mWindow.draw(text);
}

void Game::loadTextures()
{
  mTextureManager.load(TextureID::BlueX, "res/img/blueX.png");
  mTextureManager.load(TextureID::RedO, "res/img/redCircle.png");
  mTextureManager.load(TextureID::Board, "res/img/board.png");
}

void Game::loadFonts()
{
  mFontManager.load(FontID::GameStatus, "res/fonts/orbitron-light.ttf");
}

sf::Vector2u Game::getScreenSize() const
{
  auto screenWidth = sf::VideoMode::getDesktopMode().width;
  auto screenHeight = sf::VideoMode::getDesktopMode().height;
  return sf::Vector2u(screenWidth, screenHeight);
}
