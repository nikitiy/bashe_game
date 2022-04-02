#pragma once
#include <string>

using namespace std;

class Item {
protected:
	int iCount;
public:
	Item(int);
	void plusItem(int);
	void minusItem(int);
	int amountItem(void);
	string Print();
};
