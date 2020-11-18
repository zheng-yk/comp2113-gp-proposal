#include "AIplayer.h"

AIplayer::AIplayer(int color, std::string name)
{
	this->color = color;
	this->name = name;
}
Chess AIplayer::giveNextChess(const int chesspadstate[15][15])
{
	Position position;

	position = computerai.getPosition(chesspadstate, color);//calculate position

	return Chess(color, position.x, position.y);//return position
}
