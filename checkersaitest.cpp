#include "checkers.h"
#include "checkerstree.h"

using namespace std;

int main() {
	checkerboard board;
	std::string aimove;
	std::vector<std::string> moves,dmoves;	
	int	move;
	int i = 1;
	int j = 0;

	while (true) {
		checkerstree tree(board);
 		aimove = tree.maketree(4);
 		board.makemove(aimove);
 		board.showboard();
 		moves = board.legalmoves();
 		j = moves.size();
		dmoves = moves;

		i = 1;
		while(moves.size()) {
			cout << i << ") " << moves.back() << "\t" << endl;
			moves.pop_back();
			++i;
		}

		cout << "Choose move: ";
		scanf("%d",&move);
		
		if (j-move >= 0 && j-move < j) {
			board.makemove(dmoves[j-move]);
		}
		else cout << "INVALID MOVE" << endl;

		cout << endl;
		board.showboard();
		//cout << "Heuristic for White is: " << testboard.heuristic(0) << endl;

		moves = board.legalmoves();
		if (moves.size() == 0 && board.getturn() == 0) {
			cout << "Magenta Wins!" << endl;
			exit(0);
		}
		if (moves.size() == 0 && board.getturn() == 1) {
			cout << "White Wins!" << endl;
			exit(0);
		}
 	}	
	
	return 0;
}