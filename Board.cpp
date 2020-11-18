#include <iostream>
#include <iomanip>


#include "Board.h"
#include "Chess.h"
using namespace std;

void ChessBoard::addChess(Chess chess)
{

	if (chessboard_state[last_row][last_column])
		chessboard_state[last_row][last_column] -= 2;

	chess.getPosition(last_row, last_column);

	if (chess.getColor())
		chessboard_state[last_row][last_column] = 4;
	else
		chessboard_state[last_row][last_column] = 3;

}

void ChessBoard::getChessBoardState(int chessboard_state[ROWNUM][COLUMN])
{
	for (int i = 0;i < ROWNUM;i++)
		for (int j = 0;j < COLUMN;j++)
			chessboard_state[i][j] = this->chessboard_state[i][j];
}
