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
  mBoard.clear();
  mBoard.reserve(height);
  for(size_t row{0u}; row < height; ++row){
    mBoard.emplace_back(width, ' ');
  }
}

const std::vector<std::vector<char> > &Board::board() const
{
  return mBoard;
}

bool Board::makeMove(int row, int col, char playerMarker)
{
  if(!areCoordsValid(row, col)){
    return false;
  }

  if(mBoard[row][col] != ' '){
    return false;
  }
  mBoard[row][col] = playerMarker;
}

bool Board::checkForAVictory(int lastMoveRow, int lastMoveCol,
                             char playerMarker)
{
  std::cout << "Checking for a victory" << std::endl;
  std::vector<char> horisontalLine;
  std::vector<char> verticalLine;
  std::vector<char> mainDiagonal, secondaryDiagonal;

  //Horizontal
  auto colMin = lastMoveCol - mWinChain;
  auto colMax = lastMoveCol + mWinChain;
  std::cout << "colMin = " << colMin << std::endl;
  std::cout << "colMax = " << colMax << std::endl;
  for(int col = colMin; col < colMax; ++col){
      if(areCoordsValid(lastMoveRow, col)){
          horisontalLine.push_back(mBoard[lastMoveRow][col]);
      }
  }
  std::cout << "Horizontal line: " << std::endl;
  for(auto ch: horisontalLine){
    std::cout << ch;
  }
  std::cout << std::endl;
  //Vertical
  auto rowMin = lastMoveRow - mWinChain;
  auto rowMax = lastMoveRow + mWinChain;
  for(int row = rowMin; row < rowMax; ++row){
      if(areCoordsValid(row, lastMoveCol)){
          verticalLine.push_back(mBoard[row][lastMoveCol]);
      }
  }

  //Main diagonal
  rowMin = lastMoveRow - mWinChain;
  rowMax = lastMoveRow + mWinChain;
  colMin = lastMoveCol - mWinChain;
  colMax = lastMoveCol + mWinChain;
  for(int row = rowMin, col = colMin; row < rowMax && col < colMax; ++row, ++col){
      if(areCoordsValid(row, col)){
          mainDiagonal.push_back(mBoard[row][col]);
      }
  }

  std::cout << "mainDiagonal: " << std::endl;
  for(auto ch: mainDiagonal){
    std::cout << ch;
  }
  std::cout << std::endl;

  //Secondary diagonal
  std::cout << "secondary Diagonal: " << std::endl;
  rowMin = lastMoveRow - mWinChain + 1;
  rowMax = lastMoveRow + mWinChain;
  colMax = lastMoveCol + mWinChain - 1;
  colMin = lastMoveCol - mWinChain;
  std::cout << "rowMin = " << colMin << std::endl;
  std::cout << "rowMax = " << colMax << std::endl;
  std::cout << "colMin = " << colMin << std::endl;
  std::cout << "colMax = " << colMax << std::endl;
  for(int row = rowMin, col = colMax; row < rowMax && col > colMin; ++row, --col){
      std::cout << "row = " << row << std::endl;
      std::cout << "col = " << col << std::endl;
      if(areCoordsValid(row, col)){
          secondaryDiagonal.push_back(mBoard[row][col]);
      }
  }

  std::cout << "secondaryDiagonal: " << std::endl;
  for(auto ch: secondaryDiagonal){
      if(ch == ' '){
        std::cout << '_';
      } else {
        std::cout << ch;
      }

  }
  std::cout << std::endl;

  return checkRange(horisontalLine, playerMarker)
      || checkRange(verticalLine, playerMarker)
      || checkRange(mainDiagonal, playerMarker)
      || checkRange(secondaryDiagonal, playerMarker);
}

bool Board::checkIfGameOver() const
{
  for(auto &line: mBoard){
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
  for(auto &line: mBoard){
    std::fill(line.begin(), line.end(), ' ');
  }
}

bool Board::areCoordsValid(int row, int col) const
{
  return row >= 0 && row < mBoard.size() && col >= 0 && col < mBoard[row].size();
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


