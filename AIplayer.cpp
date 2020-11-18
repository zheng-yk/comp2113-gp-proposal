#include "AIplayer.h"

//set the asigned color and name for the AI
AIplayer::AIplayer(int color, std::string name)
{
	this->color = color;
	this->name = name;
}

//return the piece's feature of AI, output: color, position
Chess AIplayer::giveNextChess(const int chesspadstate[15][15])
{
	Position position;

	position = computerai.getPosition(chesspadstate, color);//calculate position

	return Chess(color, position.x, position.y);//return position
}
