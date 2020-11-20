#ifndef CHESS_H_INCLUDED
#define CHESS_H_INCLUDED

class Chess
{
private:
	int color;//
	int row;//
	int column;//

public:
	Chess(int color, int row, int column)
	{
		this->color = color;
		this->row = row;
		this->column = column;
	}
	int getColor();
	void getPosition(int &row, int &column);
	void setcolor(int color);
	void setPosition(int row, int column);
};

#endif // CHESS_H_INCLUDED
