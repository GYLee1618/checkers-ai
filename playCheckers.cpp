#include "checkers.h"

using namespace std;

int main() {
	checkerboard testboard;
	testboard.showboard();
	std::vector<std::string> moves,dmoves;	
	int	move;
	int i = 1;
	int j = 0;
	moves = testboard.legalmoves();
	while(true) {
		if (!testboard.getturn()) {
			cout << "\nWhite's Turn" << endl;
		} else cout << "\nMagenta's Turn" << endl;

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
			testboard.makemove(dmoves[j-move]);
		}
		else cout << "INVALID MOVE" << endl;

		cout << "Heuristic for White is: " << testboard.heuristic(0) << endl;

		moves = testboard.legalmoves();
		testboard.showboard();
		if (moves.size() == 0 && testboard.getturn() == 0) {
			cout << "Magenta Wins!" << endl;
			exit(0);
		}
		if (moves.size() == 0 && testboard.getturn() == 1) {
			cout << "White Wins!" << endl;
			exit(0);
		}
	}

	return 0;

}