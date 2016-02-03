#pragma once
//includes

class Game
{
public:
	Game();
	~Game();
	int run();
private:
	void initializeManagers();
	int gameLoop();
	bool isRunning();
};