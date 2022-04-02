#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <locale>

#define PORT 10000

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");

	cout << " ____           _____ _    _ ______ " << endl;
	cout << "|  _ \\   /\\    / ____| |  | |  ____|" << endl;
	cout << "| |_) | /  \\  | (___ | |__| | |__  " << endl;
	cout << "|  _ < / /\\ \\  \\___ \\|  __  |  __| " << endl;
	cout << "| |_) / ____ \\ ____) | |  | | |____ " << endl;
	cout << "|____/_/    \\_\\_____/|_|  |_|______|" << endl << endl;

	printf("ПРАВИЛА ИГРЫ:\n    |На столе расположено N предметов. Участвовать в игре может \n    |произвольное количество игроков.Каждый игрок может за один ход взять не \n    |более M предметов, причем N в 2 раза больше M. \n    |В ходе каждого кона одному из игроков случайным образом \n    |предоставляется право не брать ни одного предмета со стола, вместо этого \n    |добавить на стол некоторое количество предметов, но не более 1 / 4 взятых им \n    |ранее. \n    |Проигравшим считается игрок взявший последний предмет на столе.\n\n");

	string server_ip;
	cout << "Выберите:\n    1. Сервер на локальном компьютере\n    2. Сервер на удалённом компьютере" << endl;
	int choice;
	cin >> choice;
	if (choice == 2) {
		cout << "Введите IP адрес сервера: ";
		cin >> server_ip;
	}
	else {
		server_ip = "127.0.0.1";
	}
	


	SOCKET my_sock;
	WSADATA wsaData;
	char buff[1024];

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	my_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(PORT);
	HOSTENT* host;

	if (inet_addr(server_ip.c_str()) != INADDR_NONE) sock_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
	else {
		cout << "Некорректный IP адрес" << endl;
		return 1;
	}

	connect(my_sock, (sockaddr*)&sock_addr, sizeof(sock_addr));

	if (choice == 1) {
		cout << "Соединение с сервером установлено" << endl;
	}
	else {
		cout << "Соединение с " << server_ip << " установлено" << endl;
	}
	

	int messize;
	while ((messize = recv(my_sock, &buff[0], sizeof(buff), 0)) != SOCKET_ERROR) {
		if (messize > 1023) buff[1023] = 0;
		else buff[messize] = 0;
		cout << buff;

		string server(buff);
		if (server.find(">> ") != string::npos) {
			string command;
			cin >> command;
			send(my_sock, command.c_str(), command.size(), 0);
		}
	}

	cout << "Упс, что-то пошло не так" << endl;
	closesocket(my_sock);
	WSACleanup();
	return 1;
}