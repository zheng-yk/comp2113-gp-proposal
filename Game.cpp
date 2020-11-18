#include "Game.h"
#include <iostream>
using namespace std;

void Game::chooseMode()
{
	//choose mode
	do
    {
		resultdisplay.display("Type 0: Alone? Try man-machine mode - Can you win the AI?\nType 1: Have a partner? Try man-man mode - An icecream for the winner!\nPlease choose: ");
		cin.clear();
		cin.sync();
		cin >> mode;
	} while (2 <= mode || mode < 0);
}

//randomly assign the first player
void Game::initOrder()
{
	do {//randomly pick a number between 0 and 1
		int rdm=rand()%2;
    		//assign the first player play
   		first = rdm;
	} while (2 <= first || first < 0);
}
void Game::initOrderAName()
{

	if (mode) //man-man mode
    {
        //initialize
		resultdisplay.display("Please type in name for black (Black goes first): ");
		cin.clear();
		cin.sync();
		getline(cin,blackname);
		resultdisplay.display("Please type in name for white (Black goes first): ");
		cin.clear();
		cin.sync();
		getline(cin,whitename);
	}
	else //man-machine mode
	{
		initOrder();//initialize
		if (first)
		{
			blackname = "User";
			whitename = "AI";
		}
		else
		{
			blackname = "AI";
			whitename = "User";
		}
	}
}

void Game::initGame()
{
	chooseMode();//choose mode
	initOrderAName();//choose order and name
}

void Game::startGame()
{
	if (mode) //man-man mode
    {

		//initialize players
		PersonPlayer black(0, blackname);
		PersonPlayer white(1, whitename);
		//play
		playchess(black, white, judge, chesspad, resultdisplay);
	}
	else //man-machine mode
	{
		if (first) //man goes first
		{
			//initialize players
			AIplayer white(1, "AI");
			PersonPlayer black(0, "User");
			//play
			playchess(black, white, judge, chesspad, resultdisplay);
		}
		else//machine goes first
		{
			//initialize players
			AIplayer black(0, "AI");
			PersonPlayer white(1, "User");
			//
			playchess(black, white, judge, chesspad, resultdisplay);
		}
	}
}

void Game::playchess(Player &black, Player &white, Judge &judge, ChessBoard &chesspad, Show &resultdisplay) {
	int result;
	int state[15][15] = { 0 };
	//playing phase
	while (!(result = judge.judgeResult(state)))
    {
		if (judge.nextPlayer())
		{
			resultdisplay.display(state, "White: " + white.getName() + "\n");
			chesspad.addChess(white.giveNextChess(state));
		}
		else
		{
			resultdisplay.display(state, "Black: " + black.getName() + "\n");
			chesspad.addChess(black.giveNextChess(state));
		}
		chesspad.getChessBoardState(state);
	}
	//get result
	switch (result)
	{
	case 1:
		resultdisplay.display(state, "Black: " + black.getName() + " Winning!\nPress\"e\"to quit: ");
		break;
	case 2:
		resultdisplay.display(state, "White: " + white.getName() + " Winning!\nPress\"e\"to quit: ");
		break;
	case 3:
		resultdisplay.display(state, "Tie!\nPress\"e\"to quit: ");
		break;
	default:
		break;
	}
	//quit
	char exit;
	while(true)
	{
		cin.clear();
		cin.sync();
		cin >> exit;
		if (exit != 'e' && exit != 'E')
            cout << "Illegal input. Please press\"e\"to quit: " ;
        else
        {
            cout << "End of this program"<<endl;
            break;
        }
	}
}
