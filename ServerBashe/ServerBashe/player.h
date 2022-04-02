#pragma once
#include "item.h"
#include <vector>
#include "winsock2.h" 
enum class PlayerState { IDLE, WAITING_FOR_COMMAND };


class Player {
public:
	Player(Item*, int);
	string recieve();
	void Message(string str);
	void Send();
	bool UserWin();
	bool Move();

	bool active;
	PlayerState PlayerS;
	SOCKET sock;
	Item* items;
	unsigned int TakenItems;
	int whatDo;
	unsigned int max_item;
};