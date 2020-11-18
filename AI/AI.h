#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
#pragma once
struct Position
{
	int x;//0��14����
	int y;//0��14����
};
struct Situation
{//��ǰλ�õ���ʽ����ָ����������
	int win5;//5����
	int alive4;//��4
	int die4;//��4
	int lowdie4;//��4�ͼ��汾
	int alive3;//��3
	int tiao3;//��3
	int die3;//��3
	int alive2;//��2
	int lowalive2;//�ͼ���2
	int die2;//��2
	int nothreat;//û����в
};

class AI
{
private:
	//����״̬��־
	static const int WHITEFLAG = 2;
	static const int BLACKFLAG = 1;
	static const int NOTHINGFLAG = 0;

	//�������
	static const int WIN5 = 0;//0->5����
	static const int ALIVE4 = 1;//1->��4
	static const int DIE4 = 2;//2->��4
	static const int LOWDIE4 = 3;//3->��4�ĵͼ��汾
	static const int ALIVE3 = 4;//3->��3
	static const int TIAO3 = 5;//5->��3
	static const int DIE3 = 6;//6->��3
	static const int ALIVE2 = 7;//7->��2
	static const int LOWALIVE2 = 8;//8->�ͼ���2
	static const int DIE2 = 9;//9->��2
	static const int NOTHREAT = 10;//10->û����в

	//��ֵȼ�
	static const int LevelOne = 100000;//����
	static const int Leveltwo = 10000;//�ɻ�4 �� ˫��4 �� ��4��3
	static const int Levelthree = 5000;//˫��3
	static const int Levelfour = 1000;//��3�߼���3
	static const int Levelfive = 500;//����
	static const int Levelsix = 400;//�ͼ�����
	static const int Levelseven = 100;//����3
	static const int LevelEight = 90;//����3
	static const int LevelNight = 50;//˫��2
	static const int LevelTen = 10;//��2
	static const int LevelEleven = 9;//�ͼ���2
	static const int LevelTwelve = 5;//��3
	static const int LevelThirteen = 2;//��2
	static const int LevelFourteen = 1;//û����в
	static const int LevelFiveteen = 0;//������

	int judgeType(const int chess[9]);//�жϵ�ǰ�����������
	void getChess(int chess[9], const int state[15][15], Position position, int color, int direction);//��õ�ǰ�����������chess
	int getType(const int state[15][15], Position position, int color, int direction);//��õ�ǰ�����������
	int judgeChessSituation(const int state[15][15], Position position, int color);//�ۺ�4���������е�ǰλ��������Ƶķ���
	int giveScore(Situation situation);//�������ƣ�����
	Position maxScore(const int myscore[15][15], const int hisscore[15][15]);//�����ҵķ����Ͷ��ֵķ�����ѡȡ��������λ��

public:
	Position getPosition(const int chesspadstate[15][15], int color);//���ݵ�ǰ���ƣ������²����λ��

};

#endif // AI_H_INCLUDED
