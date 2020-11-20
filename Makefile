FLAGS = -pedantic-errors -std=c++11

AI.o: AI.cpp AI.h
	g++ $(FLAGS) -c $<

AIplayer.o: AIplayer.cpp AIplayer.h
	g++ $(FLAGS) -c $<

Board.o: Board.cpp Board.h chess.h
	g++ $(FLAGS) -c $<

chess.o: chess.cpp chess.h
	g++ $(FLAGS) -c $<

player.o: player.cpp player.h
	g++ $(FLAGS) -c $<

Game.o: Game.cpp Game.h
	g++ $(FLAGS) -c $<

Judge.o: Judge.cpp Judge.h
	g++ $(FLAGS) -c $<

PersonPlayer.o: PersonPlayer.cpp PersonPlayer.h
	g++ $(FLAGS) -c $<

show.o: show.cpp show.h
	g++ $(FLAGS) -c $<

main.o: main.cpp Game.h
	g++ $(FLAGS) -c $<

Trace.o: Trace.cpp Trace.h
	g++ $(FLAGS) -c $<

main: AI.o AIplayer.o Board.o chess.o player.o Game.o Judge.o PersonPlayer.o show.o Trace.o main.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main AI.o AIplayer.o Board.o chess.o player.o Game.o Judge.o Trace.o PersonPlayer.o show.o main.o main.tgz

tar:
	tar -czvf main.tgz *.cpp *.h

.PHONY: clean 
