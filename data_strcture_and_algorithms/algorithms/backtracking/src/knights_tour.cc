#include "knights_tour.h"

void KnightsTour(int n) {
  int** chess_board = NewTwoDimArray(n, n, -1);
  int x_move[8] = {2, 1, -1, -2, -2, -1, 1, 2};
  int y_move[8] = {1, 2, 2, 1, -1, -2, -2, -1};

  chess_board[0][0] = 0;

  if (KnightsGo(0, 0, 0, chess_board, x_move, y_move, n) == false) {
    cout << "no answer" << endl;
  }

  for (int i = 0; i < n; ++i) {
    PrintArray(chess_board[i], n);
  }
}

bool IsValid(int x, int y, int** chess_board, int n) {
  if (x >= 0 && x < n && y >= 0 && y < n && chess_board[x][y] == -1) {
    return true;
  }
  return false;
}

bool KnightsGo(int x, int y, int move_count, int** chess_board, int x_move,
               int y_move, int n) {}
