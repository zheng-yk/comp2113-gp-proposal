#include "includes.h"

int main()
{
    show_chessboard();
    //mode.cpp
    //select a mode, man-man or man-machine
    cout << "Welcome to HAPPY GOMOKU!" << endl;
    cout << "1: Alone? Try man-machine mode - Can you win the AI?" << endl;
    cout << "2: Have a partner? Try man-man mode - An icecream for the winner!" << endl;
    cout << "Please select a mode:";

    int mode;
    while (cin >> mode){
        if (mode == 1){
            cout << "You've chosen man-machine mode. Please input the coordinates of your piece:" << endl;
            break;
        }
        else if (mode == 2){
            cout << "You've chosen man-man mode. Please input the coordinates of your piece:" << endl;
            break;
        }
        else{
            cout << "You can only choose between '1' or '2'~ Please choose again~" << endl;
        }
    }

    //get coordinates
    cout << "Please input your coordinates:(sample:[y][x], 1<x,y<15)" << endl;
    int x,y;
    //check whether x,y are legal inputs
    while (cin >> x >> y){
        if (x<1||x>15||y<1||y>15)
            cout << "Illegal input. Please input legal coordinates:" << endl;
        else break;
    }

    //display pieces »¹Ã»Ð´ºÃÀ²hiahiahia

    //judge.cpp
    //judge winning situation
    int horizontal=1, vertical=1, loblique=1, roblique=1; //counter for horizontal, vertical, left-oblique, right-oblique directions
    //leftwards
    for (int i=1;i<=4;i++){
        if (chessboard[y][x-i] == chessboard[y][x] && chessboard[y][x]!=0)
            horizontal++;
        else break;
    }
    //rightwards
    for (int i=1;i<=4;i++){
        if (chessboard[y][x+i] == chessboard[y][x] && chessboard[y][x]!=0)
            horizontal++;
        else break;
    }
    //upwards
    for (int i=1;i<=4;i++){
        if (chessboard[y+i][x] == chessboard[y][x] && chessboard[y][x]!=0)
            vertical++;
        else break;
        }
    //downwards
    for (int i=1;i<=4;i++){
    if (chessboard[y-i][x] == chessboard[y][x] && chessboard[y][x]!=0)
        vertical++;
    else break;
    }
    //left diagonal - up
    for (int i=1;i<=4;i++){
        if (chessboard[y-i][x-i] == chessboard[y][x] && chessboard[y][x]!=0)
            loblique++;
        else break;
    }
    //left diagonal - down
    for (int i=1;i<=4;i++){
        if (chessboard[y+i][x-i] == chessboard[y][x] && chessboard[y][x]!=0)
            loblique++;
        else break;
    }
    //right diaganal - up
    for (int i=1;i<=4;i++){
        if (chessboard[y-i][x+i] == chessboard[y][x] && chessboard[y][x]!=0)
            loblique++;
        else break;
    }
    //right diaganal - down
    for (int i=1;i<=4;i++){
        if (chessboard[y+i][x+i] == chessboard[y][x] && chessboard[y][x]!=0)
            loblique++;
        else break;
    }
    //if "5 in a row" appears in any directions, there's a winning situation
    if (horizontal==5||vertical==5||loblique==5||roblique==5){
        if (chessboard[y][x]==1){
            cout << "player1 wins! Congrats!!!";
        }
        else
            cout << "player2 wins! Congrats!!!";
    }
}
