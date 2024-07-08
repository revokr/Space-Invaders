#pragma once
#include "block.h"
#include <vector>

using std::vector;

class Obstacle {
private:

public:
	Obstacle(Vector2 pos);
	void Draw();
	Vector2 position;
	vector<Block> blocks;
	static vector<vector<int>> grid;
};