#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
public:
  explicit Board(int width = 3, int height = 3, int winnigCombination = 3);
  const std::vector<std::vector<char> >& board() const;
  bool tryToMakeMove(int row, int col, char playerMarker);
  bool checkForAVictory(int lastMoveRow, int lastMoveCol, char playerMarker);
  bool checkIfGameOver() const;
  void clear();
private:
  void init(int width, int height);
  bool areCoordsValid(int row, int col) const;
  bool checkRange(const std::vector<char> &line, char playerMarker) const;
  std::vector<std::vector<char>> mBoard;
  int mWinChain;

};

#endif // BOARD_H
