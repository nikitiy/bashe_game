#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "initializedGames.h"
#pragma comment (lib, "ws2_32.lib")
#include "winsock2.h" 

using namespace std;


initializedGames::initializedGames(int New_item, int New_max_item, int PlayersCount) {

	item = New_item;
	max_item = New_max_item;
	Count = PlayersCount;
	Ready = false;
	items = new Item(item);
	mysocket = INVALID_SOCKET;
	Players.clear();
	step = 0;
}


bool initializedGames::StartServer(int port) {

	setlocale(LC_ALL, "Rus");

	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	mysocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);
	local_addr.sin_addr.s_addr = 0;

	bind(mysocket, (sockaddr*)&local_addr, sizeof(local_addr));

	listen(mysocket, 0x100);

	cout << "Сервер успешно запустился\n\n" << endl << endl;

	return true;
}



void initializedGames::GameSetup() {
	unsigned long iMode = 1;
	ioctlsocket(mysocket, FIONBIO, &iMode);
	time_t tm = time(NULL);

	while (true) {

		if (Ready == 0) {
			SOCKET client_socket;
			sockaddr_in client_addr;

			int client_addr_size = sizeof(client_addr);
			client_socket = accept(mysocket, (sockaddr*)&client_addr, &client_addr_size);

			if (client_socket != INVALID_SOCKET) {
				ioctlsocket(client_socket, FIONBIO, &iMode);
				HOSTENT* hst;
				hst = gethostbyaddr((char*)&client_addr.sin_addr.s_addr, 4, AF_INET);

				printf("Игрок успешно подключился!\n");

				Player* player = new Player(items, max_item);
				player->sock = client_socket;
				Players.push_back(player);

				string param;

				param += "Кол-во предметов: " + to_string(item) + "\n";
				param += "Максимальное кол-во предметов: " + to_string(max_item) + "\n";
				player->Message(param);

				if (Players.size() == Count) {
					cout << "Все игроки подключились!" << endl << endl;
					Ready = true;
				}
			}
		}
		else {
			for (int i = 0; i < Players.size(); i++) {
				Player* player = Players[i];
				if (i == step) player->active = true;
				else player->active = false;
				if (player->Move()) {
					step = (step + 1) % Count;
				}
			}

		}

	}

}