#include "AI.h"
#include <vector>
using namespace std;

//calculate and return the position of the next piece of AI
Position AI::getPosition(const int chessboard_state[15][15], int color) {
    
    int mychesspadcolor = color + 1;//sign of chessboard
    int hischesspadcolor;

    int myscore[15][15] = { 0 };//my score
    int hisscore[15][15] = { 0 };//opponent's score
    int tempstate[15][15] = { 0 };//sign of temporary state

    //check if it's the first piece
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
    if (k ==15 && h ==15) {//fist piece
        Position position = { 7,7 };//set at the middle by default
        return position;
    }

    //reset the sign of the last step
    for (int i = 0;i < 15;i++) {
        for (int j = 0;j < 15;j++) {
            if (chessboard_state[i][j]>2)
                tempstate[i][j] = chessboard_state[i][j] - 2;
            else
                tempstate[i][j] = chessboard_state[i][j];
        }
    }


    //marking
    for (int i = 0;i < 15;i++)
        for (int j = 0;j < 15;j++) {
            Position position;
            int score;

            position.x = i;
            position.y = j;
            //my score
            score = judgeChessSituation(tempstate, position, mychesspadcolor);//return the current score
            myscore[i][j] = score;

            if (mychesspadcolor == BLACKFLAG)
                hischesspadcolor = WHITEFLAG;
            else
                hischesspadcolor = BLACKFLAG;
            //opponent's score
            score = judgeChessSituation(tempstate, position, hischesspadcolor);//return the current score
            hisscore[i][j] = score;
        }

    //return the suggested position according to score
    return maxScore(myscore, hisscore);

}

//annalyse all the possible situations based on the current chessboard; return the updated value of the possible situatons
int AI::judgeChessSituation(const int state[15][15], Position position, int color) {

    Situation situation = { 0 };//record the situation viarable

    if (state[position.x][position.y])
        return LevelFiveteen;//return 0 mark if there're no place to move the chess

    for (int direction = 0;direction < 4;direction++) {//four directions: 0-horizontal, 1-vertical, 2-left-oblique, 3-right-oblique
        int type;
        type = getType(state, position, color, direction);//get types(e,g, die4, alive4, etc.)
        switch (type) {//set situation according to types
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
            //error control
            break;
        }
    }

    return giveScore(situation);//return scores according to situation
}

//analyze all the possible situations, return what type this situation belongs to
int AI::giveScore(Situation situation) {

    int die4 = situation.die4 + situation.lowdie4;
    int alive3 = situation.alive3 + situation.tiao3;
    int alive2 = situation.alive2 + situation.lowalive2;

    if (situation.win5 >= 1)
        return LevelOne;//win5

    if (situation.alive4 >= 1 || die4 >= 2 || (die4 >= 1 && alive3 >= 1))
        return Leveltwo;//alive4, doubledie4, die4 & alive3

    if (alive3 >= 2)
        return Levelthree;//doublealive3

    if (situation.die3 >= 1 && situation.alive3 >= 1)
        return Levelfour;//die3 & highalive3

    if (situation.die4 >= 1)
        return Levelfive;//highdei4

    if (situation.lowdie4 >= 1)
        return Levelsix;//lowdie4

    if (situation.alive3 >= 1)
        return Levelseven;//single-alive3

    if (situation.tiao3 >= 1)
        return LevelEight;//tiao3

    if (alive2 >= 2)
        return LevelNight;//double-alive2

    if (situation.alive2 >= 1)
        return LevelTen;//alive2

    if (situation.lowalive2 >= 1)
        return LevelEleven;//low-alive2

    if (situation.die3 >= 1)
        return LevelTwelve;//die3

    if (situation.die2 >= 1)
        return LevelThirteen;//die2

    return LevelFourteen;//no threat
}

//categorize the type of current situation
int AI::getType(const int state[15][15], Position position, int color, int direction) {
    //0->5 in a row; 1->alive4 2->die4 3->alive3
    //4->die3 5->tiao3 6->alive2 7->die2 8->nothreat 9->lowdie4
    int type;
    int chess[9] = { 0 };

    getChess(chess, state, position, color, direction);
    type = judgeType(chess);

    return type;
}

//obtain the pieces allocation case by case
void AI::getChess(int chess[9], const int state[15][15], Position position, int color, int direction) {
    int hiscolor;
    if (color == BLACKFLAG)
        hiscolor = WHITEFLAG;
    else
        hiscolor = BLACKFLAG;

    chess[4] = color;
    switch (direction) {
    case 0://horizontal

        for (int i = position.x, j = 1;j <= 4;j++) {//copy 4 units in the left
            int column = position.y - j;
            if (column < 0) {
                for (;j <= 4;j++)
                    chess[4 - j] = hiscolor;//out of the border: set opponent's color
                break;
            }
            chess[4 - j] = state[i][column];//within the border: copy array "state"
        }
        for (int i = position.x, j = 1;j <= 4;j++) {//copy 4 units in the right
            int column = position.y + j;
            if (column > 14) {
                for (;j <= 4;j++)
                    chess[4 + j] = hiscolor;//out of the border: set opponent's color
                break;
            }
            chess[4 + j] = state[i][column];//within the border: copy array "state"
        }
        break;
    case 1://vertical
        for (int j = position.y, i = 1;i <= 4;i++) {//copy upper 4 units
            int row = position.x - i;
            if (row < 0) {
                for (;i <= 4;i++)
                    chess[4 - i] = hiscolor;//out of the border: set opponent's color
                break;
            }
            chess[4 - i] = state[row][j];//within the border: copy array "state"
        }
        for (int i = 1, j = position.y;i <= 4;i++) {//copy lower 4 units
            int row = position.x + i;
            if (row > 14) {
                for (;i <= 4;i++)
                    chess[4 + i] = hiscolor;//out of the border: set opponent's color
                break;
            }
            chess[4 + i] = state[row][j];//within the border: copy array "state"
        }
        break;
    case 2://left-oblique
        for (int i = 1, j = 1;i <= 4;i++,j++) {
            int row = position.x - i;
            int column = position.y - j;
            if (row < 0 || column <0) {
                for (;i <= 4;i++)
                    chess[4 - i] = hiscolor;
                break;
            }
            chess[4 - i] = state[row][column];
        }
        for (int i = 1, j = 1;i <= 4;i++, j++) {
            int row = position.x + i;
            int column = position.y + j;
            if (row > 14 || column > 14) {
                for (;i <= 4;i++)
                    chess[4 + i] = hiscolor;
                break;
            }
            chess[4 + i] = state[row][column];
        }
        break;
    case 3://right-oblique
        for (int i = 1, j = 1;i <= 4;i++, j++) {
            int row = position.x + i;
            int column = position.y - j;
            if (row > 14 || column <0) {
                for (;i <= 4;i++)
                    chess[4 - i] = hiscolor;
                break;
            }
            chess[4 - i] = state[row][column];
        }
        for (int i = 1, j = 1;i <= 4;i++, j++) {
            int row = position.x - i;
            int column = position.y + j;
            if (row < 0  || column > 14) {
                for (;i <= 4;i++)
                    chess[4 + i] = hiscolor;
                break;
            }
            chess[4 + i] = state[row][column];
        }
        break;
    default:
        //error control
        break;
    }
}

//return the type and threat based on the chess allocation, based on how the central pieces arrange
int AI::judgeType(const int chess[9]) {
    int mycolor = chess[4];
    int hiscolor;

    int left, right;//the initial position relating to the centre
    int colorleft, colorright;//the initial color£¬(NOTHING or hiscolor)
    int count = 1;//initial number of central line

    if (mycolor == BLACKFLAG)
        hiscolor = WHITEFLAG;
    else
        hiscolor = BLACKFLAG;

    for (int i = 1;i <= 4;i++) {
        if (chess[4 - i] == mycolor)
            count++;//same color
        else {
            left = 4 - i;//save position
            colorleft = chess[4 - i];//save color
            break;
        }
    }
    for (int i = 1;i <= 4;i++) {
        if (chess[4 + i] == mycolor)
            count++;//same color
        else {
            right = 4 + i;//save position
            colorright = chess[4 + i];//save color
            break;
        }
    }


    if (count >= 5)//5 in a row
        return WIN5;

    if (count == 4)//4 in a row
    {
        if (colorleft == NOTHINGFLAG && colorright == NOTHINGFLAG)//both sides of the breaking point are empty
            return ALIVE4;//alive4
        else if (colorleft == hiscolor && colorright == hiscolor)//both sides of the breaking point are nonempty
            return NOTHREAT;//no threat
        else if (colorleft == NOTHINGFLAG || colorright == NOTHINGFLAG)//either side of the breaking point is empty
            return DIE4;//die4
    }

    if (count == 3) {//3 in a row
        int colorleft1 = chess[left - 1];
        int colorright1 = chess[right + 1];

        if (colorleft == NOTHINGFLAG && colorright == NOTHINGFLAG)//both sides of the breaking point are empty
        {

            if (colorleft1 == hiscolor && colorright1 == hiscolor)//opponent's piece
                return DIE3;
            else if (colorleft1 == mycolor || colorright1 == mycolor)//if one of the 2 are my piece
                return LOWDIE4;
            else if (colorleft1 == NOTHINGFLAG || colorright1 == NOTHINGFLAG)//if there exists one empty cell
                return ALIVE3;

        }
        else if (colorleft == hiscolor && colorright == hiscolor)//both sides of the breaking point are nonempty
        {
            return NOTHREAT;//no threat
        }
        else if (colorleft == NOTHINGFLAG || colorright == NOTHINGFLAG)//either side of the breaking point is empty
        {

            if (colorleft == hiscolor) {//blocked on the left
                if (colorright1 == hiscolor)//blocked in the right
                    return NOTHREAT;
                if (colorright1 == NOTHINGFLAG)//right: empty
                    return DIE3;
                if (colorright1 == mycolor)
                    return LOWDIE4;

            }
            if (colorright == hiscolor) {//blocked on the right
                if (colorleft1 == hiscolor)//blocked on the left
                    return NOTHREAT;
                if (colorleft1 == NOTHINGFLAG)//left: empty
                    return DIE3;
                if (colorleft1 == mycolor)//there exists my pieces in the lift
                    return LOWDIE4;
            }
        }
    }

    if (count == 2) {//2 in a row
        int colorleft1 = chess[left - 1];
        int colorright1 = chess[right + 1];
        int colorleft2 = chess[left - 2];
        int colorright2 = chess[right + 2];

        if (colorleft == NOTHINGFLAG && colorright == NOTHINGFLAG)//both sides of the breaking point are empty
        {
            if ((colorright1 == NOTHINGFLAG && colorright2 == mycolor) ||
                (colorleft1 == NOTHINGFLAG && colorleft2 == mycolor))
                return DIE3;//die3
            else if (colorleft1 == NOTHINGFLAG && colorright1 == NOTHINGFLAG)
                return ALIVE2;//alive2

            if ((colorright1 == mycolor && colorright2 == hiscolor) ||
                (colorleft1 == mycolor && colorleft2 == hiscolor))
                return DIE3;//die3

            if ((colorright1 == mycolor && colorright2 == mycolor) ||
                (colorleft1 == mycolor && colorleft2 == mycolor))
                return LOWDIE4;//die4

            if ((colorright1 == mycolor && colorright2 == NOTHINGFLAG) ||
                (colorleft1 == mycolor && colorleft2 == NOTHINGFLAG))
                return TIAO3;//tiao3
            //return "NOTHREAT" otherwise
        }
        else if (colorleft == hiscolor && colorright == hiscolor)//both sides of the breaking point are nonempty
        {
            return NOTHREAT;
        }
        else if (colorleft == NOTHINGFLAG || colorright == NOTHINGFLAG)//either side of the breaking point is empty
        {
            if (colorleft == hiscolor) {//blocked in the left
                if (colorright1 == hiscolor || colorright2 == hiscolor) {//one piece of the opponent's
                    return NOTHREAT;//no threat
                }
                else if (colorright1 == NOTHINGFLAG && colorright2 == NOTHINGFLAG) {//both empty
                    return DIE2;//die2
                }
                else if (colorright1 == mycolor && colorright2 == mycolor) {//both are my pieces
                    return LOWDIE4;//die4
                }
                else if (colorright1 == mycolor || colorright2 == mycolor) {//1 my piece
                    return DIE3;//die3
                }
            }
            if (colorright == hiscolor) {//blocked on the right
                if (colorleft1 == hiscolor || colorleft2 == hiscolor) {//1 piece of the opponent's
                    return NOTHREAT;//no threat
                }
                else if (colorleft1 == NOTHINGFLAG && colorleft2 == NOTHINGFLAG) {//both empty
                    return DIE2;//die2
                }
                else if (colorleft1 == mycolor && colorleft2 == mycolor) {//both are my pieces
                    return LOWDIE4;//die4
                }
                else if (colorleft1 == mycolor || colorleft2 == mycolor) {//only one piece of mine
                    return DIE3;//die3
                }
            }
        }
    }

    if (count == 1) {//1 in the centre
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

    }
    return NOTHREAT;//others: no threat
}

//compare the maxscore, i.e. the best moving strategy, return the suggested position for the next piece
Position AI::maxScore(const int myscore[15][15], const int hisscore[15][15]) {
    Position position = {0, 0};

    int mymaxscore = 0;//initialize to 0
    int hismaxscore = 0;

    vector<Position> mypositionvector;//store the biggest value
    vector<Position> hispositionvector;

    for (int i = 0;i < 15;i++)//set my biggest vector
        for (int j = 0;j < 15;j++) {
            if (myscore[i][j] == mymaxscore) {//add position vector
                position.x = i;
                position.y = j;
                mypositionvector.push_back(position);
            }
            if (myscore[i][j]>mymaxscore) {
                mymaxscore = myscore[i][j];//replace the biggest value
                mypositionvector.clear();//clear position vector
                //add new position vector
                position.x = i;
                position.y = j;
                mypositionvector.push_back(position);
            }
        }

    for (int i = 0;i < 15;i++)//set the vector of the opponent's
        for (int j = 0;j < 15;j++) {
            if (hisscore[i][j] == hismaxscore) {
                position.x = i;
                position.y = j;
                hispositionvector.push_back(position);
            }
            if (hisscore[i][j]>hismaxscore) {
                hismaxscore = hisscore[i][j];//replace the biggest value
                hispositionvector.clear();//clear position vector

                position.x = i;
                position.y = j;
                hispositionvector.push_back(position);
            }

        }

    if (mymaxscore >= hismaxscore) {//attack!!!!
        int temp = 0;//store opponent's greatest score

        vector<Position>::iterator iter;
        for (iter = mypositionvector.begin();iter != mypositionvector.end();iter++)
        {
            Position maxtemp = *iter;
            if (hisscore[maxtemp.x][maxtemp.y] >= temp) {
                temp = hisscore[maxtemp.x][maxtemp.y];//replace the biggest value
                position = maxtemp;//replace the position
            }
        }

        return position;//return the greatest value of the opponent's among my greatest values
    }
    else {//defend
        int temp = 0;//store my greatest score

        vector<Position>::iterator iter;
        for (iter = hispositionvector.begin();iter != hispositionvector.end();iter++)
        {
            Position maxtemp = *iter;
            if (myscore[maxtemp.x][maxtemp.y] >= temp) {
                temp = myscore[maxtemp.x][maxtemp.y];//replace the greatest value
                position = maxtemp;//replace position
            }
        }

        return position;//return the greatest value of mine among the opponent's greatest values
    }

}
