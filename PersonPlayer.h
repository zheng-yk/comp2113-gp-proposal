#ifndef PERSONPLAYER_H_INCLUDED
#define PERSONPLAYER_H_INCLUDED
#include <string>

#include "Player.h"
#include "Chess.h"
using namespace std;
class PersonPlayer :public Player
{
public:
	PersonPlayer(int color, string name);
	Chess giveNextChess(const int chessboard_state[15][15]);
};

#endif // PERSONPLAYER_H_INCLUDED
