#include <iostream>
#include <iomanip>

#include "Show.h"
using namespace std;

void Show::display(string msg)
{
	int initstate[15][15] = { 0 };
	display(initstate, msg);
}

void Show::display(const int chessboard_state[15][15], string msg)
{
	system("cls");//clear screen
	cout << rowAcolumn << endl;//row number
	for (int row = 0;row < 15;row++)
    {
		cout << rowAcolumn.at((row + 1) * 2 + 1) << " ";//row number
		for (int column = 0;column < 15;column++)
		{
			switch (chessboard_state[row][column])
			{
				case 0://blank
					cout << chesspadsymbol.at((row * 15 + column) * 2)
						<< chesspadsymbol.at((row * 15 + column) * 2 + 1);//unicode 2 bytes
					break;
				case 1://black chess
					cout << "¡ð";
					break;
				case 2://white chess
					cout << "¡ñ";
					break;
				case 3:// the final black chess
					cout << "¨Œ";
					break;
				case 4://the final white chess
					cout << "¨‹";
					break;
				default:
					break;
			}
		}
		cout << endl;
	}
	cout << msg;
}
