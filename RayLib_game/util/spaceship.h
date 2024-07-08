#pragma once
#include "laser.h"
#include <vector>
#include <iostream>

using std::vector;

class Spaceship {
private:
	Texture2D image;
	Vector2 position;
	double laserFireTime;

public:
	vector<Laser> lasers;

	Spaceship();
	~Spaceship();
	void Draw();
	Rectangle getRect();
	void MoveLeft();
	void MoveRight();
	void reset();
	void Shoot();
};