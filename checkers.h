#ifndef _CHECKERS_H
#define _CHECKERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#define BLUE "\033[1;44m"
#define RED "\033[1;41m"
#define WHITE "\033[1;37m"
#define MAGENTA "\033[1;35m"
#define BLANK "  "
#define RESET "\33[0m"
#define PIECE "()"
#define KING "|{"

class checkerboard {
private:
	int board[8][8];
	bool turn;
	int Pieces[2];

	int getPos(std::string pos,int * container) {
		*container = pos[0] - 'A';
		*(container+1) = pos[1] - '0';
		return 0;
	}

	int getJump(int i,int j,std::vector<std::string> &moves,std::string move);

	int kingJump(int i,int j,std::vector<std::string> &moves,std::string move,std::unordered_map<std::string,int> jumpedPieces,int ii, int jj);

public:
	checkerboard();

	void showboard();

	bool getturn();

	int makemove(std::string move);

	std::vector<std::string> legalmoves();

	int testWin();

	int heuristic(bool player);

	checkerboard& operator=(const checkerboard& rhs) {
		for (int i = 0;i<8;++i) {
			for (int j = 0;j<8;++j) {
				board[i][j] = rhs.board[i][j];
			}
		}
		turn = rhs.turn;
		Pieces[0] = rhs.Pieces[0];
		Pieces[1] = rhs.Pieces[1];
		return *this;
	}
};

#endif