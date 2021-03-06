#include <iostream>
#include "initializedGames.h"


using namespace std;

int main() {

	setlocale(LC_ALL, "RUS");

	int item = 0;
	int max_item = 0;
	int playersCount = 0;

	cout << " ____           _____ _    _ ______ " << endl; 
	cout << "|  _ \\   /\\    / ____| |  | |  ____|" << endl;
	cout << "| |_) | /  \\  | (___ | |__| | |__  " << endl;
	cout << "|  _ < / /\\ \\  \\___ \\|  __  |  __| " << endl;
	cout << "| |_) / ____ \\ ____) | |  | | |____ " << endl;
	cout << "|____/_/    \\_\\_____/|_|  |_|______|" << endl << endl;

	printf("ПРАВИЛА ИГРЫ:\n    |На столе расположено N предметов. Участвовать в игре может \n    |произвольное количество игроков.Каждый игрок может за один ход взять не \n    |более M предметов, причем N в 2 раза больше M. \n    |В ходе каждого кона одному из игроков случайным образом \n    |предоставляется право не брать ни одного предмета со стола, вместо этого \n    |добавить на стол некоторое количество предметов, но не более 1 / 4 взятых им \n    |ранее. \n    |Проигравшим считается игрок взявший последний предмет на столе.\n\n");

	cout << "Введите кол-во предметов: ";
	cin >> item;

	while (item < 15) {
		cout << endl << "Кол-во предметов должно быть не меньше 15, введите нормальное значение: ";
		cin >> item;
	}

	cout << "Введите максимальное кол-во забираемых предметов: ";
	cin >> max_item;

	while (max_item > (item / 5)) {
		cout << endl << "Максимальное кол-во забираемых предметов должно быть меньше, введите нормальное значение: ";
		cin >> max_item;
	}

	cout << "Введите кол-во игроков: ";
	cin >> playersCount;

	while (playersCount < 2) {
		cout << endl << "Количество игроков должно быть больше 2-х, введите нормальное значение: ";
		cin >> playersCount;
	}


	initializedGames game(item, max_item, playersCount);

	game.StartServer(10000);
	game.GameSetup();
	
}
