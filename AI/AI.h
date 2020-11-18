#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
#pragma once
struct Position
{
	int x;//row
	int y;//column
};
struct Situation
{//score
	int win5;
	int alive4;
	int die4;
	int lowdie4;
	int alive3;
	int tiao3;
	int die3;
	int alive2;
	int lowalive2;
	int die2;
	int nothreat;
};

class AI
{
private:
	//棋盘状态标志
	static const int WHITEFLAG = 2;
	static const int BLACKFLAG = 1;
	static const int NOTHINGFLAG = 0;

	//棋局类型
	static const int WIN5 = 0;//0->5 in a row
	static const int ALIVE4 = 1;//1->allive4
	static const int DIE4 = 2;//2->die4
	static const int LOWDIE4 = 3;//3->lowdie4
	static const int ALIVE3 = 4;//3->alive3
	static const int TIAO3 = 5;//5->tiao3
	static const int DIE3 = 6;//6->die3
	static const int ALIVE2 = 7;//7->alive2
	static const int LOWALIVE2 = 8;//8->lowalive2
	static const int DIE2 = 9;//9->die2
	static const int NOTHREAT = 10;//10->no threat

	//打分等级
	static const int LevelOne = 100000;//win5
	static const int Leveltwo = 10000;//alive4 or die4 or die4alive3
	static const int Levelthree = 5000;//double-alive3
	static const int Levelfour = 1000;//die&high-alive3
	static const int Levelfive = 500;//die4
	static const int Levelsix = 400;//lowdie四
	static const int Levelseven = 100;//single-live3
	static const int LevelEight = 90;//tiao3
	static const int LevelNight = 50;//double-live2
	static const int LevelTen = 10;//alive2
	static const int LevelEleven = 9;//lowdie2
	static const int LevelTwelve = 5;//die3
	static const int LevelThirteen = 2;//die2
	static const int LevelFourteen = 1;//no threat
	static const int LevelFiveteen = 0;//no place to move

	int judgeType(const int chess[9]);//judge the current situation
	void getChess(int chess[9], const int state[15][15], Position position, int color, int direction);//get the current chess array
	int getType(const int state[15][15], Position position, int color, int direction);
	int judgeChessSituation(const int state[15][15], Position position, int color);//judge the current score combining 4 directions
	Position maxScore(const int myscore[15][15], const int hisscore[15][15]);//choose the most beneficial position

public:
	Position getPosition(const int chesspadstate[15][15], int color);

};

#endif // AI_H_INCLUDED
