#pragma once
#ifndef SHOW_H_INCLUDED
#define SHOW_H_INCLUDED

#include <string>
#include <iostream>
#include <cstdlib>
class Show{
private:
	std::string rowAcolumn;
	std::string chesspadsymbol;

public:
	Show() {
		rowAcolumn = "   A B C D E F G H I J K L M N O";
		chesspadsymbol =	"���ЩЩЩЩЩЩЩЩЩЩЩЩЩ�"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"���ةةةةةةةةةةةةة�";
	}
	void display(const int chesspadstate[15][15], std::string msg);//ˢ����ʾ����
	void display(std::string msg);//��û��ʼ���壬��ʾ��Ϣ���

};


#endif // SHOW_H_INCLUDED
