#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>

#include "Chess.h"
using namespace std;

class Player
{
protected:
	int color;
	string name;
public:
	virtual Chess giveNextChess(const int chessboard_state[15][15]) = 0;
	string getName();
};


#endif // PLAYER_H_INCLUDED
