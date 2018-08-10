#include "board.hpp"

Board::Board(int width, int height)
{
  init(width, height);
}

void Board::init(int width, int height)
{
  mBoard.clear();
  mBoard.reserve(height);
  for(size_t row{0u}; row < height; ++row){
    mBoard.emplace_back(width, ' ');
    }
}

bool Board::areCoordsValid(size_t row, size_t col) const
{
  return row < mBoard.size() && col < mBoard[row].size();
}

void Board::makeMove(int row, int col)
{
  if(!areCoordsValid(row, col)){
    return;
  }
  mBoard[row][col] = isXTurn ? 'X' : 'O';
  isXTurn = !isXTurn;
}

char Board::checkWinner()
{
  return ' ';
}

void Board::clear()
{

}

const std::vector<std::vector<char> > &Board::board() const
{
  return mBoard;
}
