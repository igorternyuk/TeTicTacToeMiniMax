#ifndef AI_H
#define AI_H

#include "board.hpp"

struct AiMove{
  int row, col, score;
  AiMove() {}
  AiMove(int score): row(0), col(0) { this->score = score; }
};

class AI
{
public:
  explicit AI(char aiPlayer);
  void setAiPlayer(char aiPlayer);
  void makeMove(Board &board);
  char getAiPlayer() const;
  char getHumanPlayer() const;

private:
  AiMove getBestMove(Board &board, char player);
  char mAiPlayer, mHumanPlayer;
};

#endif // AI_H
