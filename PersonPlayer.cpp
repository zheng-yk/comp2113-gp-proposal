#include <iostream>
#include <iomanip>


#include "PersonPlayer.h"
using namespace std;

//relate color and name
PersonPlayer::PersonPlayer(int color, string name)
{
	this->color = color;
	this->name = name;
}

//display the personplayer's movement; output: personplayer's pieces' status 
Chess PersonPlayer::giveNextChess(const int chessboard_state[15][15])
{
	int x, y;
	char a, b;

	while (true)
    {
		while(true)
        {
			cout << "Please input your coordinates(sample: AB): ";
			cin.clear();
			cin.sync();
			cin >> a;
			cin >> b;
			if (!('A' <= a && a <= 'O') || !('A' <= b && b <= 'O'))
                cout << "Illegal input. Please input legal coordinates: " ;
            else
                break;
		}

		x = a - 'A';//judge if the position is occupied
		y = b - 'A';
		if (chessboard_state[x][y])//occupied
        {
			cout << "This position is occupied. Please change your choice."<<endl;
			continue;
		}
		else//legal step
			break;
	}
	return Chess(color, x, y);
}
