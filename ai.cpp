#include "ai.hpp"
#include <algorithm>

AI::AI(char aiPlayer):
  mAiPlayer(aiPlayer), mHumanPlayer(aiPlayer == 'X' ? 'O' : 'X')
{}

void AI::setAiPlayer(char aiPlayer)
{
  this->mAiPlayer = aiPlayer;
  mHumanPlayer = aiPlayer == 'X' ? 'O' : 'X';
}

void AI::makeMove(Board &board)
{
  AiMove bestMove = getBestMove(board, mAiPlayer);
  board.tryToMakeMove(bestMove.row, bestMove.col, mAiPlayer);
}

AiMove AI::getBestMove(Board &board, char player)
{
  if(board.checkForAVictory(mAiPlayer)){
    return AiMove(10);
  } else if(board.checkForAVictory(mHumanPlayer)){
    return AiMove(-10);
  } else if(board.checkIfGameOver()){
    return AiMove(0);
  }

  std::vector<AiMove> moves;
  auto grid = board.grid();
  for(size_t row{0u}; row < grid.size(); ++row){
      for(size_t col{0u}; col < grid[row].size(); ++col){
          if(grid[row][col] == ' '){
            AiMove move;
            move.row = row;
            move.col = col;
            board.tryToMakeMove(row, col, player);
            if(player == mAiPlayer){
              move.score = getBestMove(board, mHumanPlayer).score;
            } else {
              move.score = getBestMove(board, mAiPlayer).score;
            }
            moves.push_back(move);
            board.undoLastMove();
          }
      }
  }

  std::sort(moves.begin(), moves.end(), [](auto move1, auto move2){
      return move1.score < move2.score;
  });

  if(player == mAiPlayer){
    return moves[moves.size() - 1];
  } else {
    return moves[0];
  }
}

char AI::getHumanPlayer() const
{
  return mHumanPlayer;
}

char AI::getAiPlayer() const
{
  return mAiPlayer;
}
