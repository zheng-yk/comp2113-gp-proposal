#include <iostream>
#include <iomanip>


#include "Judge.h"
using namespace std;

int Judge::judgeResult(const int chessboard_state[15][15])
{
	int lastrow, lastcolumn;
	int i, j;
	int count, result;
	int rowmin, rowmax, columnmin, columnmax;


	int flag = 0;
	for (i = 0;i < 15;i++)
    {
		for (j = 0;j < 15;j++)
		{
			if (chessboard_state[i][j] == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag)
			break;
	}
	if (i == 15 && j == 15)
		return 3;//end on a tie

	flag = 0;
	for (i = 0;i < 15;i++) //position of the final step
    {
		for (j = 0;j < 15;j++)
			if (chessboard_state[i][j]>2)
			{
				lastrow = i;
				lastcolumn = j;
				result = chessboard_state[i][j] - 2;//return the sign of winning of the current player
				flag = 1;
				break;
			}
		if (flag)
			break;
	}
	if (i == 15 && j == 15)//haven't started yet
		return 0;

	//horizontal
	count = 0;
	columnmin = lastcolumn - 4 < 0 ? 0 : lastcolumn - 4;
	columnmax = lastcolumn + 4 > 14 ? 14 : lastcolumn + 4;
	for (i = lastrow, j = columnmin;j <= columnmax;j++)
    {
		if (chessboard_state[i][j] == result || chessboard_state[i][j] == result + 2)
		{
			count++;
			if (count == 5)//win
				return result;
		}
		else
			count = 0;//count again
	}

	//vertical
	count = 0;
	rowmin = lastrow - 4 < 0 ? 0 : lastrow - 4;
	rowmax = lastrow + 4 > 14 ? 14 : lastrow + 4;
	for (i = rowmin, j = lastcolumn;i <= rowmax;i++) {
		if (chessboard_state[i][j] == result || chessboard_state[i][j] == result + 2)
		{
			count++;
			if (count == 5)//win
				return result;
		}
		else
			count = 0;//count again
	}

	//left diagonal
	count = 0;
	rowmin = lastrow - 4;
	columnmin = lastcolumn - 4;
	if (rowmin < 0 || columnmin < 0) //out of range
    {
		if (lastrow > lastcolumn)
		{
			columnmin = 0;//get the boundary
			rowmin = lastrow - lastcolumn;
		}
		else
		{
			rowmin = 0;//get the boundary
			columnmin = lastcolumn - lastrow;
		}
	}
	rowmax = lastrow + 4;
	columnmax = lastcolumn + 4;
	if (rowmax > 14 || columnmax > 14) //out of range
	{
		if (14 - lastrow < 14 - lastcolumn)
		{
			rowmax = 14;//get the boundary
			columnmax = lastcolumn + 14 - lastrow;
		}
		else
		{
			columnmax = 14;
			rowmax = lastrow + 14 - lastcolumn;
		}
	}
	for (i = rowmin, j = columnmin;i <= rowmax;i++, j++)
	{
		if (chessboard_state[i][j] == result || chessboard_state[i][j] == result + 2)
		{
			count++;
			if (count == 5)//win
				return result;
		}
		else
			count = 0;//count again
	}

	//right diagonal
	count = 0;
	rowmin = lastrow - 4;
	columnmax = lastcolumn + 4;
	if (rowmin < 0 || columnmax>14) //out of range
    {
		if (lastrow - 0 < 14 - lastcolumn)
		{
			rowmin = 0;//get the boundary
			columnmax = lastcolumn + lastrow;
		}
		else
		{
			columnmax = 14;
			rowmin = lastrow - (14 - lastcolumn);
		}
	}
	rowmax = lastrow + 4;
	columnmin = lastcolumn - 4;
	if (rowmax > 14 || columnmin < 0) //out of range
	{
		if (14 - lastrow < lastcolumn - 0)
		{
			rowmax = 14;
			columnmin = lastcolumn - (14 - lastrow);
		}
		else {
			columnmin = 0;
			rowmax = lastrow + lastcolumn - 0;
		}
	}
	for (i = rowmin, j = columnmax;i <= rowmax;i++, j--)
	{
		if (chessboard_state[i][j] == result || chessboard_state[i][j] == result + 2)
		{
			count++;
			if (count == 5)//win
				return result;
		}
		else
			count = 0;//count again
	}
	return 0;//haven't get result yet
}
int Judge::nextPlayer() //next player
{
    if (current_player)
        current_player = 0;
    else
        current_player = 1;
    return current_player;
}
