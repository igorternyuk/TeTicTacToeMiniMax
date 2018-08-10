#include "game.hpp"

Game::Game()
    : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TicTacToeMiniMax") {
  auto screenWidth = sf::VideoMode::getDesktopMode().width;
  auto screenHeight = sf::VideoMode::getDesktopMode().height;
  auto dx = (screenWidth - mWindow.getSize().x) / 2;
  auto dy = (screenHeight - mWindow.getSize().y) / 2;
  mWindow.setPosition(sf::Vector2i(dx, dy));
  loadTextures();
}

void Game::run() {
  while (mWindow.isOpen()) {
    inputPhase();
    updatePhase();
    renderingPhase();
  }
}

void Game::inputPhase() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      mWindow.close();
    }
    if (event.type == sf::Event::KeyReleased) {
      switch (event.key.code) {
        case sf::Keyboard::Return:
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
        int row = event.mouseButton.y / CELL_SIZE;
        int col = event.mouseButton.x / CELL_SIZE;
        mBoard.makeMove(row, col);
    }
  }
}

void Game::updatePhase() {

}

void Game::renderingPhase() {
  mWindow.clear(sf::Color::White);
  sf::Sprite background;
  background.setTexture(mTextureManager.get(TextureID::Board));
  background.setPosition(0, 0);
  auto board = mBoard.board();
  for(size_t row{0u}; row < board.size(); ++row){
      for(size_t col{0u}; col < board[row].size(); ++col){
        if(board[row][col] == ' '){
            continue;
        }
        sf::Sprite spot;
        spot.setPosition(col * CELL_SIZE, row * CELL_SIZE);
        if(board[row][col] == 'X'){
          spot.setTexture(mTextureManager.get(TextureID::BlueX));
        } else if(board[row][col] == 'O'){
          spot.setTexture(mTextureManager.get(TextureID::RedO));
        }
        mWindow.draw(spot);
      }
  }
  mWindow.draw(background);
  mWindow.display();
}

void Game::loadTextures()
{
  mTextureManager.load(TextureID::BlueX, "res/img/blueX.png");
  mTextureManager.load(TextureID::RedO, "res/img/redCircle.png");
  mTextureManager.load(TextureID::Board, "res/img/board.png");
}
