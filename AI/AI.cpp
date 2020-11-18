#include "AI.h"
#include <vector>
using namespace std;
Position AI::getPosition(const int chessboard_state[15][15], int color) {//������һ�����ӵ�λ��
	//���ֺ����ӵı�־ + 1 = ���̵ı�־
	int mychesspadcolor = color + 1;//���̱�־
	int hischesspadcolor;

	int myscore[15][15] = { 0 };//�ҵķ���
	int hisscore[15][15] = { 0 };//���ֵķ���
	int tempstate[15][15] = { 0 };//��ʱ��־

	//�ж��Ƿ��һ������
	int flag = 0;
	int k = 0, h = 0;
	for (k = 0;k < 15;k++) {
		for (h = 0;h < 15;h++) {
			if (chessboard_state[k][h]>0) {
				flag = 1;
				break;
			}
		}
		if (flag)
			break;
	}
	if (k ==15 && h ==15) {//��һ������
		Position position = { 7,7 };//Ĭ�����м�
		return position;
	}

	//�����һ����־��ԭ
	for (int i = 0;i < 15;i++) {
		for (int j = 0;j < 15;j++) {
			if (chessboard_state[i][j]>2)
				tempstate[i][j] = chessboard_state[i][j] - 2;
			else
				tempstate[i][j] = chessboard_state[i][j];
		}
	}


	//���
	for (int i = 0;i < 15;i++)
		for (int j = 0;j < 15;j++) {
			Position position;
			int score;

			position.x = i;
			position.y = j;
			//�ҵķ���
			score = judgeChessSituation(tempstate, position, mychesspadcolor);//���ص�ǰ���Ʒ���
			myscore[i][j] = score;

			if (mychesspadcolor == BLACKFLAG)
				hischesspadcolor = WHITEFLAG;
			else
				hischesspadcolor = BLACKFLAG;
			//���ַ���
			score = judgeChessSituation(tempstate, position, hischesspadcolor);//���ص�ǰ���Ʒ���
			hisscore[i][j] = score;
		}

	//���ݷ���������λ��
	return maxScore(myscore, hisscore);

}

int AI::judgeChessSituation(const int state[15][15], Position position, int color) {

	Situation situation = { 0 };//��¼��ǰ���Ʊ���

	if (state[position.x][position.y])
		return LevelFiveteen;//���Ӳ����£�����0��

	for (int direction = 0;direction < 4;direction++) {//�ĸ�����,0�ᣬ1����2�������£�3��������
		int type;
		type = getType(state, position, color, direction);//ȡ�����ͣ����ģ����ĵȣ�

		switch (type) {//�������Ͷ�situation����
		case WIN5:
			situation.win5++;
			break;
		case ALIVE4:
			situation.alive4++;
			break;
		case DIE4:
			situation.die4++;
			break;
		case LOWDIE4:
			situation.lowdie4++;
			break;
		case ALIVE3:
			situation.alive3++;
			break;
		case TIAO3:
			situation.tiao3++;
			break;
		case DIE3:
			situation.die3++;
			break;
		case ALIVE2:
			situation.alive2++;
			break;
		case LOWALIVE2:
			situation.lowalive2++;
			break;
		case DIE2:
			situation.die2++;
			break;
		case NOTHREAT:
			situation.nothreat++;
			break;
		default:
			//������
			break;
		}
	}

	return giveScore(situation);//�������Ƶó�����
}

int AI::giveScore(Situation situation) {

	int die4 = situation.die4 + situation.lowdie4;
	int alive3 = situation.alive3 + situation.tiao3;
	int alive2 = situation.alive2 + situation.lowalive2;

	if (situation.win5 >= 1)
		return LevelOne;//Ӯ5

	if (situation.alive4 >= 1 || die4 >= 2 || (die4 >= 1 && alive3 >= 1))
		return Leveltwo;//��4 ˫��4 ��4��3

	if (alive3 >= 2)
		return Levelthree;//˫��3

	if (situation.die3 >= 1 && situation.alive3 >= 1)
		return Levelfour;//��3�߼���3

	if (situation.die4 >= 1)
		return Levelfive;//�߼���4

	if (situation.lowdie4 >= 1)
		return Levelsix;//�ͼ���4

	if (situation.alive3 >= 1)
		return Levelseven;//����3

	if (situation.tiao3 >= 1)
		return LevelEight;//����3

	if (alive2 >= 2)
		return LevelNight;//˫��2

	if (situation.alive2 >= 1)
		return LevelTen;//��2

	if (situation.lowalive2 >= 1)
		return LevelEleven;//�ͼ���2

	if (situation.die3 >= 1)
		return LevelTwelve;//��3

	if (situation.die2 >= 1)
		return LevelThirteen;//��2

	return LevelFourteen;//û����в
}

int AI::getType(const int state[15][15], Position position, int color, int direction) {
	//0->5���� 1->��4 2->��4 3->��3
	//4->��3 5->��3 6->��2 7->��2 8->nothreat 9->�ͼ���4
	int type;
	int chess[9] = { 0 };

	getChess(chess, state, position, color, direction);
	type = judgeType(chess);

	return type;
}

void AI::getChess(int chess[9], const int state[15][15], Position position, int color, int direction) {
	int hiscolor;//�߽���������
	if (color == BLACKFLAG)
		hiscolor = WHITEFLAG;
	else
		hiscolor = BLACKFLAG;

	chess[4] = color;
	switch (direction) {
	case 0://����

		for (int i = position.x, j = 1;j <= 4;j++) {//���󿽱��ĸ�
			int column = position.y - j;
			if (column < 0) {
				for (;j <= 4;j++)
					chess[4 - j] = hiscolor;//�������ö�����ɫ
				break;
			}
			chess[4 - j] = state[i][column];//û���磬����state����
		}
		for (int i = position.x, j = 1;j <= 4;j++) {//���ҿ����ĸ�
			int column = position.y + j;
			if (column > 14) {
				for (;j <= 4;j++)
					chess[4 + j] = hiscolor;//�������ö�����ɫ
				break;
			}
			chess[4 + j] = state[i][column];//û���磬����state����
		}
		break;
	case 1://����
		for (int j = position.y, i = 1;i <= 4;i++) {//���Ͽ����ĸ�
			int row = position.x - i;
			if (row < 0) {
				for (;i <= 4;i++)
					chess[4 - i] = hiscolor;//�������ö�����ɫ
				break;
			}
			chess[4 - i] = state[row][j];//û���磬����state����
		}
		for (int i = 1, j = position.y;i <= 4;i++) {//���¿����ĸ�
			int row = position.x + i;
			if (row > 14) {
				for (;i <= 4;i++)
					chess[4 + i] = hiscolor;//�������ö�����ɫ
				break;
			}
			chess[4 + i] = state[row][j];//û���磬����state����
		}
		break;
	case 2://����
		for (int i = 1, j = 1;i <= 4;i++,j++) {//�����Ͽ����ĸ�
			int row = position.x - i;
			int column = position.y - j;
			if (row < 0 || column <0) {//����һ�����߽�
				for (;i <= 4;i++)
					chess[4 - i] = hiscolor;//�������ö�����ɫ
				break;
			}
			chess[4 - i] = state[row][column];//û���磬����state����
		}
		for (int i = 1, j = 1;i <= 4;i++, j++) {//�����¿����ĸ�
			int row = position.x + i;
			int column = position.y + j;
			if (row > 14 || column > 14) {//����һ�����߽�
				for (;i <= 4;i++)
					chess[4 + i] = hiscolor;//�������ö�����ɫ
				break;
			}
			chess[4 + i] = state[row][column];//û���磬����state����
		}
		break;
	case 3://����
		for (int i = 1, j = 1;i <= 4;i++, j++) {//�����¿����ĸ�
			int row = position.x + i;
			int column = position.y - j;
			if (row > 14 || column <0) {//����һ�����߽�
				for (;i <= 4;i++)
					chess[4 - i] = hiscolor;//�������ö�����ɫ
				break;
			}
			chess[4 - i] = state[row][column];//û���磬����state����
		}
		for (int i = 1, j = 1;i <= 4;i++, j++) {//�����Ͽ����ĸ�
			int row = position.x - i;
			int column = position.y + j;
			if (row < 0  || column > 14) {//����һ�����߽�
				for (;i <= 4;i++)
					chess[4 + i] = hiscolor;//�������ö�����ɫ
				break;
			}
			chess[4 + i] = state[row][column];//û���磬����state����
		}
		break;
	default:
		//������
		break;
	}
}

int AI::judgeType(const int chess[9]) {
	int mycolor = chess[4];
	int hiscolor;

	int left, right;//��ʼ�������߶Ͽ���λ��
	int colorleft, colorright;//��ʼ�������߶Ͽ�����ɫ��NOTHING����hiscolor
	int count = 1;//�������ж��ٸ�����ʼ��

	if (mycolor == BLACKFLAG)
		hiscolor = WHITEFLAG;
	else
		hiscolor = BLACKFLAG;

	for (int i = 1;i <= 4;i++) {
		if (chess[4 - i] == mycolor)
			count++;//ͬɫ
		else {
			left = 4 - i;//����Ͽ�λ��
			colorleft = chess[4 - i];//����Ͽ���ɫ
			break;
		}
	}
	for (int i = 1;i <= 4;i++) {
		if (chess[4 + i] == mycolor)
			count++;//ͬɫ
		else {
			right = 4 + i;//����Ͽ�λ��
			colorright = chess[4 + i];//����Ͽ���ɫ
			break;
		}
	}


	if (count >= 5)//������5��
		return WIN5;//5����

	if (count == 4)//������4��
	{
		if (colorleft == NOTHINGFLAG && colorright == NOTHINGFLAG)//���߶Ͽ�λ�þ���
			return ALIVE4;//����
		else if (colorleft == hiscolor && colorright == hiscolor)//���߶Ͽ�λ�þ��ǿ�
			return NOTHREAT;//û����в
		else if (colorleft == NOTHINGFLAG || colorright == NOTHINGFLAG)//���߶Ͽ�λ��ֻ��һ����
			return DIE4;//����
	}

	if (count == 3) {//������3��
		int colorleft1 = chess[left - 1];
		int colorright1 = chess[right + 1];

		if (colorleft == NOTHINGFLAG && colorright == NOTHINGFLAG)//���߶Ͽ�λ�þ���
		{

			if (colorleft1 == hiscolor && colorright1 == hiscolor)//��Ϊ��������
				return DIE3;
			else if (colorleft1 == mycolor || colorright1 == mycolor)//ֻҪһ��Ϊ�Լ�������
				return LOWDIE4;
			else if (colorleft1 == NOTHINGFLAG || colorright1 == NOTHINGFLAG)//ֻҪ��һ����
				return ALIVE3;

		}
		else if (colorleft == hiscolor && colorright == hiscolor)//���߶Ͽ�λ�þ��ǿ�
		{
			return NOTHREAT;//û����в
		}
		else if (colorleft == NOTHINGFLAG || colorright == NOTHINGFLAG)//���߶Ͽ�λ��ֻ��һ����
		{

			if (colorleft == hiscolor) {//��߱��Է���ס
				if (colorright1 == hiscolor)//�ұ�Ҳ���Է���ס
					return NOTHREAT;
				if (colorright1 == NOTHINGFLAG)//�ұ߾���
					return DIE3;
				if (colorright1 == mycolor)
					return LOWDIE4;

			}
			if (colorright == hiscolor) {//�ұ߱��Է���ס
				if (colorleft1 == hiscolor)//���Ҳ���Է���ס
					return NOTHREAT;
				if (colorleft1 == NOTHINGFLAG)//��߾���
					return DIE3;
				if (colorleft1 == mycolor)//��߻����Լ�������
					return LOWDIE4;
			}
		}
	}

	if (count == 2) {//������2��
		int colorleft1 = chess[left - 1];
		int colorright1 = chess[right + 1];
		int colorleft2 = chess[left - 2];
		int colorright2 = chess[right + 2];

		if (colorleft == NOTHINGFLAG && colorright == NOTHINGFLAG)//���߶Ͽ�λ�þ���
		{
			if ((colorright1 == NOTHINGFLAG && colorright2 == mycolor) ||
				(colorleft1 == NOTHINGFLAG && colorleft2 == mycolor))
				return DIE3;//��3
			else if (colorleft1 == NOTHINGFLAG && colorright1 == NOTHINGFLAG)
				return ALIVE2;//��2

			if ((colorright1 == mycolor && colorright2 == hiscolor) ||
				(colorleft1 == mycolor && colorleft2 == hiscolor))
				return DIE3;//��3

			if ((colorright1 == mycolor && colorright2 == mycolor) ||
				(colorleft1 == mycolor && colorleft2 == mycolor))
				return LOWDIE4;//��4

			if ((colorright1 == mycolor && colorright2 == NOTHINGFLAG) ||
				(colorleft1 == mycolor && colorleft2 == NOTHINGFLAG))
				return TIAO3;//����3
			//����������±߷���NOTHREAT
		}
		else if (colorleft == hiscolor && colorright == hiscolor)//���߶Ͽ�λ�þ��ǿ�
		{
			return NOTHREAT;
		}
		else if (colorleft == NOTHINGFLAG || colorright == NOTHINGFLAG)//���߶Ͽ�λ��ֻ��һ����
		{
			if (colorleft == hiscolor) {//��߱��Է���ס
				if (colorright1 == hiscolor || colorright2 == hiscolor) {//ֻҪ�жԷ���һ������
					return NOTHREAT;//û����в
				}
				else if (colorright1 == NOTHINGFLAG && colorright2 == NOTHINGFLAG) {//����
					return DIE2;//��2
				}
				else if (colorright1 == mycolor && colorright2 == mycolor) {//��Ϊ�Լ�������
					return LOWDIE4;//��4
				}
				else if (colorright1 == mycolor || colorright2 == mycolor) {//ֻ��һ���Լ�������
					return DIE3;//��3
				}
			}
			if (colorright == hiscolor) {//�ұ߱��Է���ס
				if (colorleft1 == hiscolor || colorleft2 == hiscolor) {//ֻҪ�жԷ���һ������
					return NOTHREAT;//û����в
				}
				else if (colorleft1 == NOTHINGFLAG && colorleft2 == NOTHINGFLAG) {//����
					return DIE2;//��2
				}
				else if (colorleft1 == mycolor && colorleft2 == mycolor) {//��Ϊ�Լ�������
					return LOWDIE4;//��4
				}
				else if (colorleft1 == mycolor || colorleft2 == mycolor) {//ֻ��һ���Լ�������
					return DIE3;//��3
				}
			}
		}
	}

	if (count == 1) {//������1��
		int colorleft1 = chess[left - 1];
		int colorright1 = chess[right + 1];
		int colorleft2 = chess[left - 2];
		int colorright2 = chess[right + 2];
		int colorleft3 = chess[left - 3];
		int colorright3 = chess[right + 3];

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == mycolor)
			return LOWDIE4;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == mycolor)
			return LOWDIE4;

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == NOTHINGFLAG && colorright == NOTHINGFLAG)
			return TIAO3;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == NOTHINGFLAG && colorleft == NOTHINGFLAG)
			return TIAO3;

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == hiscolor && colorright == NOTHINGFLAG)
			return DIE3;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == hiscolor && colorleft == NOTHINGFLAG)
			return DIE3;

		if (colorleft == NOTHINGFLAG && colorleft1 == NOTHINGFLAG &&
			colorleft2 == mycolor && colorleft3 == mycolor)
			return DIE3;
		if (colorright == NOTHINGFLAG && colorright1 == NOTHINGFLAG &&
			colorright2 == mycolor && colorright3 == mycolor)
			return DIE3;

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == NOTHINGFLAG && colorleft3 == mycolor)
			return DIE3;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == NOTHINGFLAG && colorright3 == mycolor)
			return DIE3;

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == NOTHINGFLAG && colorleft3 == NOTHINGFLAG && colorright == NOTHINGFLAG)
			return LOWALIVE2;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == NOTHINGFLAG && colorright3 == NOTHINGFLAG && colorleft == NOTHINGFLAG)
			return LOWALIVE2;

		if (colorleft == NOTHINGFLAG && colorleft1 == NOTHINGFLAG &&
			colorleft2 == mycolor && colorleft3 == NOTHINGFLAG && colorright == NOTHINGFLAG)
			return LOWALIVE2;
		if (colorright == NOTHINGFLAG && colorright1 == NOTHINGFLAG &&
			colorright2 == mycolor && colorright3 == NOTHINGFLAG && colorleft == NOTHINGFLAG)
			return LOWALIVE2;

		//�������±߷���û����в

	}
	return NOTHREAT;//����û����в
}

Position AI::maxScore(const int myscore[15][15], const int hisscore[15][15]) {
	Position position = {0, 0};

	int mymaxscore = 0;//��ʼ��Ϊ0
	int hismaxscore = 0;

	vector<Position> mypositionvector;//�洢���ֵ��Ӧ��λ������
	vector<Position> hispositionvector;

	for (int i = 0;i < 15;i++)//�����ҵ����ֵ����
		for (int j = 0;j < 15;j++) {
			if (myscore[i][j] == mymaxscore) {//���λ����������
				position.x = i;
				position.y = j;
				mypositionvector.push_back(position);
			}
			if (myscore[i][j]>mymaxscore) {//�϶��д���0�ķ���
				mymaxscore = myscore[i][j];//�滻���ֵ
				mypositionvector.clear();//���λ����������
				//�����λ������
				position.x = i;
				position.y = j;
				mypositionvector.push_back(position);
			}
		}

	for (int i = 0;i < 15;i++)//���ö��ֵ����ֵ����
		for (int j = 0;j < 15;j++) {
			if (hisscore[i][j] == hismaxscore) {
				position.x = i;
				position.y = j;
				hispositionvector.push_back(position);
			}
			if (hisscore[i][j]>hismaxscore) {//�϶��д���0�ķ���
				hismaxscore = hisscore[i][j];//�滻���ֵ
				hispositionvector.clear();//���λ����������

				position.x = i;
				position.y = j;
				hispositionvector.push_back(position);
			}

		}

	if (mymaxscore >= hismaxscore) {//����
		int temp = 0;//�洢��������Щλ���е�������

		vector<Position>::iterator iter;
		for (iter = mypositionvector.begin();iter != mypositionvector.end();iter++)
		{
			Position maxtemp = *iter;
			if (hisscore[maxtemp.x][maxtemp.y] >= temp) {//�϶������
				temp = hisscore[maxtemp.x][maxtemp.y];//�滻���ֵ
				position = maxtemp;//�滻λ��
			}
		}

		return position;//�����ҵ����ֵ�ж���Ҳ����λ��
	}
	else {//����
		int temp = 0;//�洢�Լ�����Щλ���е�������

		vector<Position>::iterator iter;
		for (iter = hispositionvector.begin();iter != hispositionvector.end();iter++)
		{
			Position maxtemp = *iter;
			if (myscore[maxtemp.x][maxtemp.y] >= temp) {//�϶������
				temp = myscore[maxtemp.x][maxtemp.y];//�滻���ֵ
				position = maxtemp;//�滻λ��
			}
		}

		return position;//���ض��ֵ����ֵ����Ҳ����λ��
	}

}

