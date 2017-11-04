#include "checkers.h"

checkerboard::checkerboard() {
	char tmp[32];
	/*
	do {
		std::cout << "First move goes to:\n1)White\n2)Magenta" << std::endl;
		scanf("%s",tmp);

		if (atoi(tmp) <= 2 && atoi(tmp) >= 1) {
			turn = atoi(tmp)-1;
		}
		else {
			std::cout << "INVALID OPTION" << std::endl;
		}
	}while(atoi(tmp) > 2 || atoi(tmp) < 1);*/
	turn = 1;

	for (int i = 0;i < 3;++i) {
		for (int j = 0;j < 8;++j) {
			if ((i+j) % 2 == 0) {
				board[i][j] = 1;
			}
			else {
				board[i][j] = 0;
			}
		}
	}
	for (int i = 5;i < 8;++i) {
		for (int j = 0;j < 8;++j) {
			if ((i+j) % 2 == 0) {
				board[i][j] = 2;
			}
			else {
				board[i][j] = 0;
			}
		}
	}
	for (int i = 3;i < 5;++i) {
		for (int j = 0;j < 8;++j) {
			board[i][j] = 0;
		}
	}
	Pieces[0] = 12;
	Pieces[1] = 12;
}

void checkerboard::showboard() {
	std::cout << " A B C D E F G H" << std::endl;
	for (int i = 0;i < 8;++i) {
		std::cout << i;
		for (int j = 0; j < 8; ++j) {
			if ((i+j) % 2 == 0) {
				std::cout << BLUE;
			}
			else std::cout << RED;
			switch(board[i][j]) {
				case 0:
					std::cout << BLANK;
					break;
				case 1:
					std::cout << WHITE << PIECE;
					break;
				case 2:
					std::cout << MAGENTA << PIECE;
					break;
				case -1:
					std::cout << WHITE << KING;
					break;
				case -2:
					std::cout << MAGENTA << KING;
					break;
				default:
					break;
			}
		}
		std::cout << RESET << BLANK << std::endl;
	}
	//cout << Pieces[0] << Pieces[1] << endl;
}

bool checkerboard::getturn() {
	return turn;
}

int checkerboard::getJump(int i,int j,std::vector<std::string> &moves,std::string move) {
	std::string move2 = move;
	bool recurs = 0;
	if(abs(board[i-2*turn+1][j+1]) == 2-turn && j+2 < 8 && i-4*turn+2 < 8 && i-4*turn+2 >= 0 && board[i-4*turn+2][j+2] == 0) {
		//cout << 1 << endl;			
		move.append(1,(char) (j+2)+'A');
		move.append(1,(char) (i-4*turn+2)+'0');
		getJump(i-4*turn+2,j+2,moves,move);
		recurs = 1;
	}
	if(abs(board[i-2*turn+1][j-1]) == 2-turn && j-2 >= 0 && i-4*turn+2 < 8 && i-4*turn+2 >= 0 && board[i-4*turn+2][j-2] == 0) {
		//cout << 2 << endl;
		move2.append(1,(char) (j-2)+'A');
		move2.append(1,(char) (i-4*turn+2)+'0');
		getJump(i-4*turn+2,j-2,moves,move2);
		recurs = 1;
	}
	
	if (recurs == 0) {
		if (move.size()>2){
			moves.push_back(move);
			return 1;
		}
		return 0;
	}

	return 1;
}

int checkerboard::kingJump(int i,int j,std::vector<std::string> &moves,std::string move,std::unordered_map<std::string,int> jumpedPieces,int ii,int jj) {
	std::string piece = "",move3,move4;
	std::string move2 = (move3 = (move4 = move));
	std::unordered_map<std::string,int> jumpedPieces3,jumpedPieces4;
	std::unordered_map<std::string,int> jumpedPieces2 = (jumpedPieces3 = (jumpedPieces4 = jumpedPieces)); 
	int recurs = 0;
	if(abs(board[i+1][j+1]) == 2-turn && j+2 < 8 && i+2 < 8 && (board[i+2][j+2] == 0 || (i+2 == ii && j+2 == jj))) {
		piece.append(1,(char) (j+1)+'A');
		piece.append(1,(char) (i+1)+'0');
		auto k = jumpedPieces.emplace(piece,1);
		if (std::get<1>(k)) {
			move.append(1,(char) (j+2)+'A');
			move.append(1,(char) (i+2)+'0');
			kingJump(i+2,j+2,moves,move,jumpedPieces,ii,jj);
			recurs = 1;
		}
	}
	piece = "";
	if(abs(board[i+1][j-1]) == 2-turn && j-2 >= 0 && i+2 < 8 && (board[i+2][j-2] == 0 || (i+2 == ii && j-2 == jj))) {
		piece.append(1,(char) (j-1)+'A');
		piece.append(1,(char) (i+1)+'0');
		auto k = jumpedPieces2.emplace(piece,1);
		if (std::get<1>(k)) {
			move2.append(1,(char) (j-2)+'A');
			move2.append(1,(char) (i+2)+'0');
			kingJump(i+2,j-2,moves,move2,jumpedPieces2,ii,jj);
			recurs = 1;
		}
	}
	piece = "";
	if(abs(board[i-1][j+1]) == 2-turn && j+2 < 8 && i-2 >= 0 && (board[i-2][j+2] == 0 || (i-2 == ii && j+2 == jj))) {		
		piece.append(1,(char) (j+1)+'A');
		piece.append(1,(char) (i-1)+'0');
		auto k = jumpedPieces3.emplace(piece,1);
		if (std::get<1>(k)) {
			move3.append(1,(char) (j+2)+'A');
			move3.append(1,(char) (i-2)+'0');
			kingJump(i-2,j+2,moves,move3,jumpedPieces3,ii,jj);
			recurs = 1;
		}
	}
	piece = "";
	if(abs(board[i-1][j-1]) == 2-turn && j-2 >= 0 && i-2 >= 0 && (board[i-2][j-2] == 0 || (i-2 == ii && j-2 == jj))) {
		piece.append(1,(char) (j-1)+'A');
		piece.append(1,(char) (i-1)+'0');
		auto k = jumpedPieces4.emplace(piece,1);
		if (std::get<1>(k)) {
			move4.append(1,(char) (j-2)+'A');
			move4.append(1,(char) (i-2)+'0');
			kingJump(i-2,j-2,moves,move4,jumpedPieces4,ii,jj);
			recurs = 1;
		}
	}
	
	if (recurs == 0) {	
		if (move.size()>2){
			moves.push_back(move);
			return 1;
		}
		return 0;
	}

	return 1;
}

std::vector<std::string> checkerboard::legalmoves() {
	int end = 0;
	std::string move;
	std::vector<std::string> jmoves,moves;
	std::unordered_map<std::string,int> jumpedPieces;
	for(int i = 0; i < 8; ++i) {
		for(int j = i % 2; j < 8; j += 2) {
			if (board[i][j] == turn + 1) {
				move = "";
				move.append(1,(char) (j)+'A');
				move.append(1,(char) (i)+'0');
				getJump(i,j,jmoves,move);
				move = "";
				move.append(1,(char) (j)+'A');
				move.append(1,(char) (i)+'0');
				if(board[i-2*turn+1][j+1] == 0 && j+1 < 8) {
					move.append(1,(char) (j+1)+'A');
					move.append(1,(char) (i-2*turn+1)+'0');
					moves.push_back(move);
				}
				move = "";
				move.append(1,(char) (j)+'A');
				move.append(1,(char) (i)+'0');
				if(board[i-2*turn+1][j-1] == 0 && j-1 >= 0) {
					move.append(1,(char) (j-1)+'A');
					move.append(1,(char) (i-2*turn+1)+'0');
					moves.push_back(move);
				}
			}
			if (board[i][j] == -turn - 1) {
				move = "";
				move.append(1,(char) (j)+'A');
				move.append(1,(char) (i)+'0');
				kingJump(i,j,jmoves,move,jumpedPieces,i,j);
				move = "";
				move.append(1,(char) (j)+'A');
				move.append(1,(char) (i)+'0');
				if(board[i+1][j+1] == 0 && j+1 < 8 && i+1 < 8) {
					move.append(1,(char) (j+1)+'A');
					move.append(1,(char) (i+1)+'0');
					moves.push_back(move);
				}
				move = "";
				move.append(1,(char) (j)+'A');
				move.append(1,(char) (i)+'0');
				if(board[i+1][j-1] == 0 && j-1 >= 0 && i+1 < 8) {
					move.append(1,(char) (j-1)+'A');
					move.append(1,(char) (i+1)+'0');
					moves.push_back(move);
				}
				if(board[i-1][j+1] == 0 && j+1 < 8 && i-1 >=0 ) {
					move.append(1,(char) (j+1)+'A');
					move.append(1,(char) (i-1)+'0');
					moves.push_back(move);
				}
				move = "";
				move.append(1,(char) (j)+'A');
				move.append(1,(char) (i)+'0');
				if(board[i-1][j-1] == 0 && j-1 >= 0 && i-1 >= 0) {
					move.append(1,(char) (j-1)+'A');
					move.append(1,(char) (i-1)+'0');
					moves.push_back(move);
				}
			}
		}
	}
	if (jmoves.size()) {
		return jmoves;
	}
	else return moves;
}

int checkerboard::makemove(std::string move) {
	int pos[2],newpos[2];
	int i = 2;
	pos[0] = move[0] - 'A';
	pos[1] = move[1] - '0';
	do {
		newpos[0] = move[i] - 'A';
		newpos[1] = move[i+1] - '0';
		board[newpos[1]][newpos[0]] = board[pos[1]][pos[0]];
		board[pos[1]][pos[0]] = 0;
		if (abs(newpos[0] - pos[0]) == 2) {
			board[abs(newpos[1]+pos[1])/2][abs(newpos[0]+pos[0])/2] = 0;
			--Pieces[!turn];
		}
		if (!turn && newpos[1] == 7 || turn && newpos[1] == 0) {
			board[newpos[1]][newpos[0]] = -(turn + 1);
		}
		i+=2;
		pos[0] = newpos[0];
		pos[1] = newpos[1];
	}while(i+1 < move.size());
	turn = !turn;

	return 0;
}

int checkerboard::testWin() {
	if (Pieces[0] == 0) {
		return 0;
	}
	if (Pieces[1] == 0) {
		return 1;
	}
	return -1;
}

int checkerboard::heuristic(bool player) {
	return Pieces[player]-Pieces[!player];
}