#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include "Chess.h"
class ChessBoard
{
private:
	int last_row;
	int last_column;
	static const int ROWNUM = 15;
	static const int COLUMN = 15;
	int chessboard_state[ROWNUM][COLUMN];

public:
	ChessBoard()
	{
		last_row = 0;
		last_column = 0;
		for (int i = 0;i < ROWNUM;i++)
			for (int j = 0;j < COLUMN;j++)
				chessboard_state[i][j] = 0;
	}
	void addChess(Chess chess);
	void getChessBoardState(int chessboard_state[15][15]);
};

#endif // BOARD_H_INCLUDED
