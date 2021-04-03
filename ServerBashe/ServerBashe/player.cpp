#include <time.h>
#include <iostream>
#include "item.h"
#include "player.h"

using namespace std;

Player::Player(Item* own_item, int mi) {
	whatDo = 0;
	max_item = mi;
	sock = INVALID_SOCKET;
	PlayerS = PlayerState::IDLE;
	active = false;
	items = own_item;
	TakenItems = 0;
}


void Player::Message(string str) {
	string send_str = "\n" + str + "\n";

	if (sock != INVALID_SOCKET) {
		send(sock, send_str.c_str(), send_str.size(), 0);
	}
	else {
		cout << send_str;
	}
}

void Player::Send() {
	string str = ">> ";
	if (sock != INVALID_SOCKET) {
		send(sock, str.c_str(), str.size(), 0);
	}
	else {
		cout << str;
	}
}

bool Player::Move() {
	bool ret = false;

	if (active) {

		if (PlayerS == PlayerState::IDLE) {
			whatDo = rand() % 2;

			if (TakenItems < 4) {
				whatDo = 0;
			}

			Message(items->Print());
			if (whatDo == 0) {
				Message("Введите количество забираемых предметов, не более " + to_string(max_item));
			}
			else {
				Message("Введите количество отдаваемых предметов, не более " + to_string((int)(TakenItems / 4)));
			}

			Send();
			PlayerS = PlayerState::WAITING_FOR_COMMAND;
		}

		if (PlayerS == PlayerState::WAITING_FOR_COMMAND) {
			string command;
			int n = 0;

			if (sock != INVALID_SOCKET) {
				command = recieve();

				if (command.size()) {
					cout << whatDo << endl;
					unsigned int n = atoi(command.c_str());
					if (whatDo == 0) {
						items->minusItem(n);
						Message(items->Print());

						TakenItems += n;

						if (UserWin()) {
							Message("Поздравляем, вы выиграли!");
						}
					}
					else {
						items->plusItem(n);
						Message(items->Print());

						TakenItems -= n;
					}

					active = false;
					ret = true;
					PlayerS = PlayerState::IDLE;
				}
			}
		}
	}

	return ret;
}

string Player::recieve() {
	char buff[1024];
	int len = recv(sock, &buff[0], sizeof(buff), 0);
	if (len > 0) {
		if (len > 1023) buff[1023] = 0;
		else buff[len] = 0;
		return buff;
	}
	else return "";
}

bool Player::UserWin() {
	return (items->amountItem() == 0);
}