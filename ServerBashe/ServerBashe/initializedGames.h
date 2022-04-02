#pragma once
#include "player.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <winsock2.h>
#include <windows.h>

using namespace std;

class initializedGames {
public:
	initializedGames(int, int, int);
	SOCKET mysocket;

	bool StartServer(int port);
	void GameSetup();

	Item* items;
	vector<Player*> Players;
	int step;
	int item;
	int max_item;
	int Count;
	bool Ready;
};
