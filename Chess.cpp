#include <iostream>
#include <iomanip>

#include "Variables.h"
#include "Chess.h"
using namespace std;

int Chess::getColor()
{
    return color;
}

void Chess::getPosition(int &row, int &column)
{
    row = this->row;
    column = this->column;
}

void Chess::setcolor(int color)
{
    this->color = color;
}

void Chess::setPosition(int row, int column)
{
    this->row = row;
    this->column = column;
}
