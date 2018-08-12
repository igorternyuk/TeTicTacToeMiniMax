#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "resourceindentifiers.hpp"
#include "resourcemanager.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

class Game
{
public:
  explicit Game();
  enum class Status { X_WON, O_WON, TIE, PLAYING };
  void run();
  enum {

    CELLS_IN_WIDTH = 3,
    CELLS_IN_HEIGHT = 3,
    WINDOW_WIDTH = 500,
    WINDOW_HEIGHT = 500,
    CELL_SIZE = WINDOW_WIDTH / CELLS_IN_WIDTH,
  };
private:
  void newGame();
  void inputPhase();
  void updatePhase();
  void renderingPhase();
  void loadTextures();
  Board mBoard;
  Status mStatus = Status::PLAYING;
  bool mIsXTurn = true;
  sf::RenderWindow mWindow;
  TextureManager mTextureManager;
};

#endif // GAME_H
