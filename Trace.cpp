#include <iostream>
#include <iomanip>


#include "Trace.h"
using namespace std;
Trace * head = NULL;
void newStep(Trace * & head, int row, int column)
{
    Trace * new_step = new Trace;
	new_step->row = row;
	new_step->column = column;
	new_step->next = head;
	head = new_step;
}

void deleteStep(Trace * after)
{
    Trace * p = after->next;
    after->next = p->next;
    delete p;
}
