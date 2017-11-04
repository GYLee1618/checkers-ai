#ifndef CHECKERSTREE_H
#define CHECKERSTREE_H

#include "checkers.h"
#include <vector>
#include <string>
#include <iostream>

class checkerstree {
private:
	class node {
	public:
		checkerboard testboard;
		std::vector<node*> children{std::vector<node*>(100,NULL)};
		std::string move = "";
		node * parent;
		int value;
	};
	node root;
	std::string makechildren(node &parent,int depth,bool isRoot);

public:
	checkerstree(checkerboard current);

	std::string maketree(int depth);

	std::string minimax();

};
#endif
