#ifndef JUDGE_H_INCLUDED
#define JUDGE_H_INCLUDED

class Judge
{
private:
	int current_player;//0 black, 1 white

public:
	Judge()
	{
		current_player = 1;
	}

	int judgeResult(const int chessboard_state[15][15]);//judge results: 0->cannot determine;1->black wins;2->white wins;3->tie
	int nextPlayer();
};

#endif // JUDGE_H_INCLUDED
