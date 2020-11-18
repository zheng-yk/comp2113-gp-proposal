#include "AIplayer.h"

AIplayer::AIplayer(int color, std::string name)
{
	this->color = color;
	this->name = name;
}
Chess AIplayer::giveNextChess(const int chesspadstate[15][15])
{
	Position position;

	position = computerai.getPosition(chesspadstate, color);//计算位置

	return Chess(color, position.x, position.y);//返回棋子对象
}
