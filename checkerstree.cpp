#include "checkerstree.h"

checkerstree::checkerstree(checkerboard current) {
	root.testboard = current;
}

std::string checkerstree::maketree(int depth) {
	return makechildren(root,depth,1);
}

std::string checkerstree::makechildren(node &parent,int depth,bool isRoot) {
	std::string move;
	std::vector<std::string> legalmoves = parent.testboard.legalmoves();
	int k = 0;
	int heuristic;
	checkerboard tmp;
	for(int i = 0;i < legalmoves.size(); ++i) {
		tmp = parent.testboard;
		tmp.makemove(legalmoves[i]);
		node * newnode = new node;
		newnode->testboard = tmp;
		newnode->parent = &parent;
		parent.value = 2*newnode->testboard.getturn()-1*-13;
		if (isRoot) {
			newnode->move = legalmoves[i];
		}
		else newnode->move = parent.move;
		
		parent.children[i] = newnode;

		if (depth == 1) {
			heuristic = newnode->testboard.heuristic(newnode->testboard.getturn());
			if((heuristic > parent.value && newnode->testboard.getturn()) ||
				(heuristic < parent.value && !newnode->testboard.getturn())) {
				parent.value = heuristic;
				move = newnode->move;
			}
			return move;
		} else move = makechildren(*parent.children[i],depth-1,0);
		if((heuristic > parent.value && newnode->testboard.getturn()) ||
			(heuristic < parent.value && !newnode->testboard.getturn())) {
			parent.value = heuristic;
			move = newnode->move;
		}
	}
	return move;
}
