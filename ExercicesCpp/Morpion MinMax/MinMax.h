#pragma once
#include "Grid.h"
#include <vector>
#include <optional>

class MinMax
{
	MinMaxTree root;
};

class MinMaxTree {
private:
	std::vector<TreeNode> childs;
};


class TreeNode {
public:
	int getScore();
private:
	std::optional<int> score;
	Grid configuration;
	std::vector<TreeNode> childs;
};