#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
public:
  explicit Board(int width = 3, int height = 3);
  const std::vector<std::vector<char> >& board() const;
  void makeMove(int row, int col);
  char checkWinner();
  void clear();
private:
  void init(int width, int height);
  bool areCoordsValid(size_t row, size_t col) const;
  std::vector<std::vector<char>> mBoard;
  bool isXTurn = true;
};

#endif // BOARD_H
