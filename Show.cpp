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
    cout << "     A";
    for (int i=0;i<14;i++){
        char j;
        j = 'B'+i;
        cout << "   " << j;
    }
    cout << endl;
    //print the chessboard out. represent every cell as "·"
    for (int h=0;h<14;h++)
    {
        char j;
        j = 'A'+h;
        cout <<setw(3)<<setiosflags(ios::left)<< j << "  ";
        for (int l=0;l<15;l++)
        {
            switch(chessboard_state[h][l])
            {
                case 0: // blank space
                    cout << blank<<"  ";
                    break;
                case 1://black chess
                    cout << black<<"  ";
                    break;
                case 2://white chess
                    cout << white<<"  ";
                    break;
                case 3://the last black chess
                    cout << black_last<<"  ";
                    break;
                case 4://the last white chess
                    cout << white_last<<"  ";
                    break;
            }
        }
        cout << endl;
    }


	cout << msg;
}
