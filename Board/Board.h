#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "Board.cpp"
class ChessBoard {
private:
	int last_row;
	int last_column;
	static const int ROWNUM = 15;
	static const int COLUMN = 15;
	int chessboard_state[ROWNUM][COLUMN];

public:
	ChessPad() {
		lastrow = 0;
		lastcolumn = 0;
		for (int i = 0;i < ROWNUM;i++)
			for (int j = 0;j < COLUMN;j++)
				chesspadstate[i][j] = 0;
	}
	void addChess(Chess chess);
	void getChessPadState(int chesspadstate[15][15]);
};

#endif // BOARD_H_INCLUDED
