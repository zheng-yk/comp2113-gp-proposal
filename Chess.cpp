#include <iostream>
#include <iomanip>


#include "Chess.h"
using namespace std;

//return the color feature of the piece
int Chess::getColor()
{
    return color;
}

//return the position feature of the piece
void Chess::getPosition(int &row, int &column)
{
    row = this->row;
    column = this->column;
}

//set the color feature of the piece
void Chess::setcolor(int color)
{
    this->color = color;
}

//set the position feature of the piece
void Chess::setPosition(int row, int column)
{
    this->row = row;
    this->column = column;
}
