#include <iostream>
#include <iomanip>
#include <string.h>
#include "../Variables.h"
#include "Initialize.h"

using namespace std;
void initialize_chessboard()
{
    for (int h=0;h<15;h++)
    {
        for (int l=0;l<15;l++)
        {
            chessboard[h][l] = 0;
            cout<<"";
        }
    }
}

void initialize_sign()
{
    strcpy(blank, "¡¤");
    strcpy(black_chess, "¡ñ");
    strcpy(white_chess,"¡ð");
}
