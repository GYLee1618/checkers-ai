playCheckers.exe: checkers.o playCheckers.o
	g++ -o playCheckers.exe checkers.o playCheckers.o -std=c++11
checkers.o: checkers.h checkers.cpp
	g++ -c checkers.cpp -std=c++11
playCheckers.o: checkers.h playCheckers.cpp
	g++ -c playCheckers.cpp -std=c++11