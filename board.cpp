#include "board.hpp"
#include <algorithm>
#include <iostream>

Board::Board(int width, int height, int winnigCombination):
  mWinChain{winnigCombination}
{
  init(width, height);
}

void Board::init(int width, int height)
{
  mGrid.clear();
  mGrid.reserve(height);
  for(size_t row{0u}; row < height; ++row){
    mGrid.emplace_back(width, ' ');
  }
}

const std::vector<std::vector<char> > &Board::grid() const
{
  return mGrid;
}

int Board::lastMoveCol() const
{
  return !mHistory.empty() ? mHistory.top().second: 0;
}

int Board::lastMoveRow() const
{
  return !mHistory.empty() ? mHistory.top().first : 0;
}

bool Board::tryToMakeMove(int row, int col, char playerMarker)
{
  if(!areCoordsValid(row, col)){
    return false;
  }

  if(mGrid[row][col] != ' '){
    return false;
  }
  mGrid[row][col] = playerMarker;
  mHistory.push(std::make_pair(row, col));
  return true;
}

void Board::undoLastMove()
{
  if(!mHistory.empty()){
    auto lastMove = mHistory.top();
    mGrid[lastMove.first][lastMove.second] = ' ';
    mHistory.pop();
  }
}

bool Board::checkForAVictory(char playerMarker)
{
  std::vector<char> horisontalLine;
  std::vector<char> verticalLine;
  std::vector<char> mainDiagonal, secondaryDiagonal;

  //Horizontal
  auto colMin = lastMoveCol() - mWinChain;
  auto colMax = lastMoveCol() + mWinChain;
  for(int col = colMin; col < colMax; ++col){
      if(areCoordsValid(lastMoveRow(), col)){
          horisontalLine.push_back(mGrid[lastMoveRow()][col]);
      }
  }

  //Vertical
  auto rowMin = lastMoveRow() - mWinChain;
  auto rowMax = lastMoveRow() + mWinChain;
  for(int row = rowMin; row < rowMax; ++row){
      if(areCoordsValid(row, lastMoveCol())){
          verticalLine.push_back(mGrid[row][lastMoveCol()]);
      }
  }

  //Main diagonal
  for(int row = rowMin, col = colMin; row < rowMax && col < colMax; ++row, ++col){
      if(areCoordsValid(row, col)){
          mainDiagonal.push_back(mGrid[row][col]);
      }
  }

  //Secondary diagonal
  for(int row = rowMin, col = colMax; row < rowMax && col > colMin; ++row, --col){

      if(areCoordsValid(row, col)){
          secondaryDiagonal.push_back(mGrid[row][col]);
      }
  }

  return checkRange(horisontalLine, playerMarker)
      || checkRange(verticalLine, playerMarker)
      || checkRange(mainDiagonal, playerMarker)
      || checkRange(secondaryDiagonal, playerMarker);
}

bool Board::checkIfGameOver() const
{
  for(auto &line: mGrid){
      auto blankSpotCount = std::count_if(line.begin(), line.end(),
                                          [](char marker){
          return marker == ' ';
      });
      if(blankSpotCount != 0){
          return false;
      }
  }
  return true;
}

void Board::clear()
{
  for(auto &line: mGrid){
    std::fill(line.begin(), line.end(), ' ');
  }
}

bool Board::areCoordsValid(int row, int col) const
{
  return row >= 0 && row < mGrid.size() && col >= 0 && col < mGrid[row].size();
}

bool Board::checkRange(const std::vector<char> &line, char playerMarker) const
{
  int maxInARow = 0;
  for(auto marker: line){
    if(marker == playerMarker){
      ++maxInARow;
      if(maxInARow == mWinChain){
        return true;
      }
    } else {
      maxInARow = 0;
    }
  }
  return false;
}


