#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int twoPlayers = 0;
//choose man-AI or man-man mode
void Game::chooseMode()
{
	//choose mode
	do
    {
		resultdisplay.display("Type 0: Alone? Try man-machine mode - Can you win the AI?\nType 1: Have a partner? Try man-man mode - An icecream for the winner!\nPlease choose: ");
		cin.clear();
		cin.sync();
		cin >> mode;
		if (mode == 1)
            twoPlayers = 1;
	} while (2 <= mode || mode < 0);
}

//randomly dicide who would play first
void Game::initOrder()
{
	//initialize
	//randomly assign the first player
    resultdisplay.display("The order is random. Press any key to start: ");
    char start;
    cin.clear();
    cin.sync();
    cin>>start;
    srand(time(0));
    int rdm=rand()%2;
    //assign the first player
    first = rdm;//if rdm=1, you play first
}

//set plaers' names
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

//initialization of the game
void Game::initGame()
{
	chooseMode();//choose mode
	initOrderAName();//choose order and name
}

//start the game
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

//players move in term, with judgement being executed after every movement
void Game::playchess(Player &black, Player &white, Judge &judge, ChessBoard &chesspad, Show &resultdisplay)
{
	int result;
	int state[15][15] = { 0 };
	//playing phase
    while (!(result = judge.judgeResult(state)))
    {
        if (judge.nextPlayer())
        {
            resultdisplay.display(state, "White: " + white.getName() + "\n");
            if (twoPlayers)
            {
                cout << "Would you like to trace back to the previous status? (Please press 'y' to confirm and press 'n' to continue)" << endl;
                char regret;
                cin >> regret;
                while(!(regret == 'y' || regret == 'n'))
                {
                    cout << "Illegal input! Please choose again~: ";
                    cin >> regret;
                }
                if (regret=='y')
                {
                    chesspad.traceSteps(head);
                    chesspad.getChessBoardState(state);
                    resultdisplay.display(state, "White has recalled one step.\n");
                }
                chesspad.addChess(white.giveNextChess(state));
            }
            else
                chesspad.addChess(white.giveNextChess(state));
        }
		else
		{
			resultdisplay.display(state, "Black: " + black.getName() + "\n");
			if (twoPlayers)
            {
                cout << "Would you like to trace back to the previous status? (Please press 'y' to confirm and press 'n' to continue)" << endl;
                char regret;
                cin >> regret;
                while(!(regret == 'y' || regret == 'n'))
                {
                    cout << "Illegal input! Please choose again~: ";
                    cin >> regret;
                }
                if (regret=='y')
                {
                    chesspad.traceSteps(head);
                    chesspad.getChessBoardState(state);
                    resultdisplay.display(state, "Black has recalled one step.\n");
                }
                chesspad.addChess(black.giveNextChess(state));
            }
            else
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
