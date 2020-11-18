#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>

#include "Show.h"
#include "Chess.h"
#include "Board.h"
#include "PersonPlayer.h"
#include "AIplayer.h"
#include "Judge.h"
using namespace std;
class Game
{
private:
	int mode;
	int first;//Choose to be the first or not when playing with AI
	string blackname, whitename;

	Show resultdisplay;
	ChessBoard chesspad;
	Judge judge;

	void chooseMode();
	void initOrderAName();
	void initOrder();
	void playchess(Player &black, Player &white, Judge &judge, ChessBoard &chesspad, Show &resultdisplay);
public:
	Game() {
		mode = -1;
	}
	void initGame();
	void startGame();
};

#endif // GAME_H_INCLUDED
