#include "game.h"
#include <fstream>

Game::Game() {
	initGame();
}

vector<Alien> Game::CreateAliens() {
	vector<Alien> aliens;
	int cellsize = 55;
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 11; col++) {
			int alienType = 3;
			if (row > 0 && row < 3) alienType = 2;
			if (row > 2 && row < 5) alienType = 1;
			float x = col * cellsize + 205;
			float y = row * cellsize + 70;
			aliens.push_back(Alien(alienType, { x, y }));
			
		}
	}
	return aliens;
}

vector<Obstacle> Game::CreateObstacles() {
	int obsWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obsWidth)) / 5;

	for (int i = 0; i < 4; i++) {
		float offsetX = (i + 1) * gap + i * obsWidth;
		obstacles.push_back(Obstacle({ offsetX + 1, float(GetScreenHeight() - 200) }));
	}
	return obstacles;
}

void Game::Update() {
	if (run) {
		double currenttime = GetTime();
		if (currenttime - lastMysterySpawned >= mysteryShipSpawnInterval) {
			mysteryShip.Spawn();
			lastMysterySpawned = GetTime();
			mysteryShipSpawnInterval = GetRandomValue(10, 20);
		}

		for (auto& l : ship.lasers) {
			l.Update();
		}

		moveAliens();

		alienShoot();

		for (auto& laser : alienLasers) {
			laser.Update();
		}

		deleteLasers();
		mysteryShip.Update();
		checkForCollisions();
	}
	else if (IsKeyPressed(KEY_ENTER)) {
		reset();
		initGame();
	}
}

void Game::Draw() {
	ship.Draw();

	for (auto& obs : obstacles) {
		obs.Draw();
	}

	for (auto& alien : aliens) {
		alien.Draw();
	}

	for (auto& laser : alienLasers) {
		laser.Draw();
	}

	mysteryShip.Draw();
}

void Game::handleInput() {

	if (run) {
		if (IsKeyDown(KEY_A)) {
			ship.MoveLeft();
		}
		if (IsKeyDown(KEY_D)) {
			ship.MoveRight();
		}
		if (IsKeyDown(KEY_SPACE)) {
			ship.Shoot();
		}
	}
}

void Game::moveAliens() {
	for (auto& alien : aliens) {
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 10) {
			aliensDirection = -1;
			moveDownAliens(4);
		}
		if (alien.position.x < 10 ) {
			aliensDirection = 1;
			moveDownAliens(4);
		}
		alien.Update(aliensDirection);

	}
}

void Game::moveDownAliens(int distance) {
	for (auto& alien : aliens) {
		alien.position.y += distance;
	}
}

void Game::checkForCollisions() {
	// Spaceship lasers
	for (auto& laser : ship.lasers) {
		auto it = aliens.begin();
		while (it != aliens.end() && laser.active == true) {
			if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
				score += 100 * it->getType();
				checkScore();
				std::cout << "Score is : " << score << '\n';
				it = aliens.erase(it);
				laser.active = false;
			}
			else {
				it++;
			}
		}
	}

	for (auto& laser : ship.lasers) {
		for (auto& obs : obstacles) {
			auto it = obs.blocks.begin();
			while (it != obs.blocks.end() /* && laser.active == true*/) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					laser.active = false;
					break;
				}
				else {
					it++;
				}
			}
		}
	}

	// mystery ship
	for (auto& laser : ship.lasers) {
		if (CheckCollisionRecs(laser.getRect(), mysteryShip.getRect())) {
			score += 500;
			checkScore();
			mysteryShip.alive = false;
			break;
		}
	}

	// blocks
	for (auto& laser : alienLasers) {
		for (auto& obs : obstacles) {
			auto it = obs.blocks.begin();
			while (it != obs.blocks.end() && laser.active == true) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = obs.blocks.erase(it);
					laser.active = false;
				}
				else {
					it++;
				}
			}
		}

		if (CheckCollisionRecs(laser.getRect(), ship.getRect())) {
			laser.active = false;
			lives--;
			if (lives == 0) {
				GameOver();
			}
		}
	}

	for (auto& alien : aliens) {
		for (auto& obs : obstacles) {
			auto it = obs.blocks.begin();
			while (it != obs.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
					it = obs.blocks.erase(it);
				}
				else {
					it++;
				}
			}
		}

		if (CheckCollisionRecs(alien.getRect(), ship.getRect())) {
			std::cout << "Spaceship HIT!!!\n";
		}
	}
}

void Game::GameOver() {
	run = false;
	std::cout << "Game Over!!\n";
}

void Game::reset() {
	ship.reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();

}

void Game::initGame() {
	obstacles = CreateObstacles();

	aliens = CreateAliens();
	aliensDirection = 1;
	alienLastFired = 0;

	lastMysterySpawned = 0;
	mysteryShipSpawnInterval = GetRandomValue(10, 20);

	lives = 3;
	run = true;
	score = 0;
	HIscore = loadHiScore();
}

void Game::checkScore() {
	if (score > HIscore) {
		HIscore = score;
		saveHiScore(HIscore);
	}
}

void Game::saveHiScore(int hiscore) {
	std::ofstream score_file("util/highscore.txt");

	score_file << HIscore;

	score_file.close();
}

int Game::loadHiScore() {
	std::ifstream score_file("util/highscore.txt");

	int loaded = 0;
	score_file >> loaded;

	score_file.close();

	return loaded;
}

void Game::deleteLasers() {
	for (auto it = ship.lasers.begin(); it != ship.lasers.end();) {
		if (!it->active) {
			std::cout << ship.lasers.size() << " ";
			it = ship.lasers.erase(it);
		}
		else {
			it++;
		}
	}
	for (auto it = alienLasers.begin(); it != alienLasers.end();) {
		if (!it->active) {
			std::cout << alienLasers.size() << " ";
			it = alienLasers.erase(it);
		}
		else {
			it++;
		}
	}
}

void Game::alienShoot() {
	double currentTime = GetTime();

	if (currentTime - alienLastFired >= alienLaserShootInterval && !aliens.empty()) {
		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2,
										alien.position.y + alien.alienImages[alien.type - 1].height }, 5));
		alienLastFired = GetTime();
	}
}


Game::~Game() {
	Alien::unloadImages();
}
