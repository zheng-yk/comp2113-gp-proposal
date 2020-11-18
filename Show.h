#pragma once
#ifndef SHOW_H_INCLUDED
#define SHOW_H_INCLUDED

#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
class Show{
private:
	string blank;
	string black;
	string white;
	string black_last;
	string white_last;

public:
	Show()
	{
		blank = "~";
		black = "*";
		white = "o";
		black_last = "-";
		white_last = "+";
	}
	void display(const int chesspadstate[15][15], std::string msg);//clear board and display
	void display(std::string msg);//initial display

};


#endif // SHOW_H_INCLUDED
