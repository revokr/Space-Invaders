#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mistery_ship.h"

class Game {
private:
	Spaceship ship;
	MysteryShip mysteryShip;
	vector<Obstacle> obstacles;
	vector<Alien> aliens;
	vector<Laser> alienLasers;
	int aliensDirection;
	constexpr static double alienLaserShootInterval = 0.55;
	float alienLastFired;
	float mysteryShipSpawnInterval;
	float lastMysterySpawned;
	

	vector<Alien> CreateAliens();
	vector<Obstacle> CreateObstacles();
	void deleteLasers();
	void alienShoot();
	void moveAliens();
	void moveDownAliens(int distance);
	void checkForCollisions();
	void GameOver();
	void reset();
	void initGame();
	void checkScore();
	void saveHiScore(int hiscore);
	int loadHiScore();
public:
	Game();
	~Game();
	void Update();
	void Draw();
	void handleInput();
	bool run;
	int lives;
	int score;
	int HIscore;
};