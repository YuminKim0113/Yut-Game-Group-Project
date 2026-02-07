FLAGS = -pedantic-errors -std=c++11

Map.o: Map.cpp Map.h Station.h MapChartDisplay.h
	g++ $(FLAGS) -c $<

MapChartDisplay.o: MapChartDisplay.cpp MapChartDisplay.h
	g++ $(FLAGS) -c $<

Player.o: Player.cpp Player.h
	g++ $(FLAGS) -c $<

Functions.o: Functions.cpp Functions.h Map.h Player.h Station.h
	g++ $(FLAGS) -c $<

main.o: main.cpp Functions.h Map.h Player.h Station.h Mal.h
	g++ $(FLAGS) -c $<

game: main.o Functions.o Player.o MapChartDisplay.o Map.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f game main.o Functions.o Player.o MapChartDisplay.o Map.o *.txt
	touch Games.txt

tar:
	tar -czvf game.tgz *.cpp *.h

.PHONY: clean tar
