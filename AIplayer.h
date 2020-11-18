#ifndef AIPLAYER_H_INCLUDED
#define AIPLAYER_H_INCLUDED
#include "Player.h"
#include "AI.h"

class AIplayer :public Player
{
private:
	AI computerai;//AI class
public:
	AIplayer(int color, std::string name);
	Chess giveNextChess(const int chesspadstate[15][15]);//calculate the next step
};


#endif // AIPLAYER_H_INCLUDED
