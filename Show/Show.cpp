#include <iostream>
#include <iomanip>

#include "../Variables.h"
#include "Show.h"
using namespace std;

void show_chessboard()
{
    cout << "   A";
    for (int i=0;i<14;i++){
        char j;
        j='B'+i;
        cout << "  " << j;
    }
    cout << endl;

    for (int h=0;h<15;h++){
        cout << setw(3) << setiosflags(ios::left) << h+1;
        for (int l=0;l<15;l++){
            switch(chessboard[h][l]){
                case 0:
                    cout << blank << " ";
                    break;
                case 1://black
                    cout << black_chess << " ";
                    break;
                case 2://white
                    cout << white_chess << " ";
                    break;
            }
        }
        cout << endl;
    }
}

