#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

class Trace//recall the last step of the current player
{
public:
    int column;
    int row;
    Trace * next;
};
void newStep(Trace * & head, int row, int column);
void deleteStep(Trace * after);


extern Trace * head;
#endif // TRACE_H_INCLUDED
