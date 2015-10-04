#ifndef KNIGHTS_TOUR_H_
#define KNIGHTS_TOUR_H_

#include <iostream>

#include "utilities.h"

using std::cout;
using std::endl;

void KnightsTour(int n);
bool IsValid(int x, int y, int** chess_board, int n);
bool KnightsGo(int x, int y, int move_count, int** chess_board, int x_move,
               int y_move, int n);

#endif
